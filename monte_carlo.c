#include "monte_carlo.h"
#include "engine.h"
#include "pcg_basic.h"
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define CELLS (BOARD_MAX_MEMORY_SIZE * BOARD_MAX_MEMORY_SIZE)
#define MAX_THREADS 64
typedef struct { const board_t *board; char player; unsigned count, id; unsigned wins[CELLS], losses[CELLS]; } worker_t;

static void* simulate(void *arg) {
    worker_t *w = arg;
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, (uint64_t)time(NULL) ^ ((uint64_t)(uintptr_t)&rng), w->id + 1);
    int empty[CELLS], nempty=0, n=w->board->size;
    for(int r=0;r<n;r++) for(int c=0;c<n;c++) if(w->board->data[r][c]=='.') empty[nempty++]=r*n+c;
    for(unsigned k=0;k<w->count;k++) for(int first=0;first<nempty;first++) {
        int idx=empty[first]; board_t b=*w->board; b.data[idx/n][idx%n]=w->player;
        int remaining[CELLS], nr=0;
        for(int j=0;j<nempty;j++) if(j!=first) remaining[nr++]=empty[j];
        char p=(w->player=='x')?'o':'x';
        int winner = game_state(&b);
        while(winner==0 && nr>0) {
            unsigned pick=pcg32_boundedrand_r(&rng,(uint32_t)nr); int cell=remaining[pick];
            b.data[cell/n][cell%n]=p; remaining[pick]=remaining[--nr]; p=(p=='x')?'o':'x';
            winner=game_state(&b);
        }
        // game_state devuelve 1/2; player contiene 'x'/'o'
        int ai_winner = w->player == 'x' ? 1 : 2;
        if(winner==ai_winner) w->wins[idx]++;
        else w->losses[idx]++;
    }
    return NULL;
}

int monte_carlo_move(const board_t *board, char player, unsigned simulations, unsigned threads) {
    if(!board || (player!='x' && player!='o') || simulations==0) return -1;
    if(threads < 1) threads = 1;
    if(threads > MAX_THREADS) threads = MAX_THREADS;
    pthread_t ids[MAX_THREADS]; worker_t workers[MAX_THREADS];
    unsigned started=0;
    for(unsigned i=0;i<threads;i++) {
        workers[i]=(worker_t){.board=board,.player=player,.count=simulations/threads+(i<simulations%threads),.id=i};
        if(pthread_create(&ids[i],NULL,simulate,&workers[i])!=0) break;
        started++;
    }
    for(unsigned i=0;i<started;i++) pthread_join(ids[i],NULL);
    if(started==0) return -1;
    unsigned wins[CELLS]={0}, losses[CELLS]={0};
    int n=board->size, best=-1, best_score=INT32_MIN;
    for(unsigned t=0;t<started;t++) for(int i=0;i<CELLS;i++) {
        wins[i]+=workers[t].wins[i]; losses[i]+=workers[t].losses[i];
    }
    for(int r=0;r<n;r++) for(int c=0;c<n;c++) {
        int i=r*n+c;
        if(board->data[r][c]!='.') continue;
        int score=(int)wins[i]-(int)losses[i];
        // printf("%c%d: %u / %u / %+d\n",'A'+c,r+1,wins[i],losses[i],score);
        if(score>best_score) { best=i; best_score=score; }
    }
    // if(best>=0) printf("Elección: %c%d (score %+d)\n",'A'+best%n,best/n+1,best_score);
    return best;
}
