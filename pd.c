#include <stdlib.h>
#include <soundpipe.h>
#include <sporth.h>
#include <string.h>
#include "m_pd.h"
#include "m_imp.h"
#include "s_stuff.h"

#define TIMEUNITPERMSEC (32. * 441.)
#define TIMEUNITPERSECOND (TIMEUNITPERMSEC * 1000.)

/* user data. */
typedef struct {
    t_pd *pd;
    int counter;
} sporth_pd_data;

static int sporth_pd(plumber_data *pd, sporth_stack *stack, void **ud)
{
    sporth_pd_data *foo;
    const char *filename;
    switch(pd->mode) {
        case PLUMBER_CREATE:
            fprintf(stderr, "Creating our custom gain plugin!\n");
            if(sporth_check_args(stack, "s") != SPORTH_OK) {
                plumber_print(pd,"Not enough arguments for pd\n");
                stack->error++;
                return PLUMBER_NOTOK;
            }
            /* malloc and assign address to user data */
            foo = malloc(sizeof(sporth_pd_data));
            *ud = foo;
            sporth_stack_pop_string(stack);
            sporth_stack_push_float(stack, 0.0);
            break;
        case PLUMBER_INIT:
            foo = *ud;
            filename = sporth_stack_pop_string(stack);
            foo->counter = 0;
            pd_init();
            sys_printtostderr = 1;
            sys_verbose = 1;
            foo->pd = glob_evalfile(NULL, gensym(filename), gensym("./"));
            sched_set_using_audio(SCHED_AUDIO_CALLBACK);
            sys_setchsr(0, 1, pd->sp->sr);
            STUFF->st_time_per_dsp_tick = (TIMEUNITPERSECOND) *
                ((double)STUFF->st_schedblocksize) / STUFF->st_dacsr; 
            sporth_stack_push_float(stack, 0.0);
            plumber_print(pd, "dac size is %d chan: %d sr: %g\n", 
                    STUFF->st_schedblocksize, STUFF->st_outchannels,
                    STUFF->st_dacsr);
            break;

        case PLUMBER_COMPUTE:
            foo = *ud;
            if(foo->counter == 0) { 
                memset(STUFF->st_soundout, 0, 
                        STUFF->st_schedblocksize * sizeof(t_sample));
                sched_tick();
            }
            sporth_stack_push_float(stack, STUFF->st_soundout[foo->counter]);
            foo->counter = (foo->counter + 1) % (STUFF->st_schedblocksize);
            break;

        case PLUMBER_DESTROY:
            foo = *ud;
            pd_free(foo->pd);
            free(foo);
            break;
    }
    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
    return sporth_pd;
}
