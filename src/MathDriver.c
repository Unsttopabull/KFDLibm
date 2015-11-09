#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/i387.h>
#include <linux/string.h>
#include <linux/slab.h>

#define KMATH

#ifdef KMATH
	#include "fdlibm.h"
	#include "MathConstants.h"
	
	#define DEG2RAD(x) ((x * M_PI) / 180.0)
#endif

/*****************************************************************************/

//~ void printFloat(char* format, float f, float f2) { 
	//~ unsigned int i1 = 0;
	//~ memcpy(&i1, &f, sizeof(f));
	//~ 
	//~ unsigned int i2 = 0;
	//~ memcpy(&i2, &f, sizeof(f));	
	//~ 
	//~ printk(KERN_INFO format, i1, i2);
//~ }

#ifdef KMATH
 
void testMath(){
    kernel_fpu_begin();
    
    int kot = 0;

    while(kot <= 360) {
        double rad = DEG2RAD(kot);
        double s = sin(rad);
        double c = cos(rad);

        double as = asin(rad);
        double ac = acos(rad);

        //printk(KERN_INFO "deg: %+d: %#08x, %#08x, %#08x, %#08lx\n", kot, s, c, as, ac);
        kot +=1;
    }

    printk(KERN_INFO "\n");

    double s = 5.33;
    //printk(KERN_INFO "SQRT:(%#08lx) = %#08lx\n", s, sqrt(s));
    s = 0;
    //printk(KERN_INFO "SQRT:(%#08lx) = %#08lx\n", s, sqrt(s));

    //printk(KERN_INFO "TAN:  %#08lx\n", tan(-24141.323));
    //printk(KERN_INFO "TANH: %#08lx\n", tanh(-24141.323));
    //printk(KERN_INFO "TANH: %#08lx\n", tanh(1));
    //printk(KERN_INFO "TANH: %#08lx\n", tanh(-1));
    //printk(KERN_INFO "TANH: %#08lx\n", tanh(M_PI / 2));
    //printk(KERN_INFO "TANH: %#08lx\n", tanh(0));
    //printk(KERN_INFO "SIN(PI /3.33): %#08lx\n", sin(M_PI / 3.33));

    double p = pow(33.3,2.4);
    //printk(KERN_INFO "POW: %#08lx\n", p);

    double t = log(33.3);
    //printk(KERN_INFO "LOG: %#08lx\n", t);

    double t10 = log10(-5);
    //printFloat("error: %s\n", strerror(errno));
    //printk(KERN_INFO "LOG10: %#08lx\n", t10);

    //printk(KERN_INFO "isNan log10(-5): %s", isnan(t10) ? "true" : "false");
    
    kernel_fpu_end();	
}
#endif

void returnDoubleParam(float* output){
	*output = 0.5f;
}

float* returnDouble(void){
	float* output = (float*) kmalloc(sizeof(float), GFP_KERNEL);
	*output = 0.5f;
	return output;
}

int __init init_mini_module(void) {
    printk(KERN_INFO "Started.\n");
    
#ifdef KMATH
    testMath();
#endif
    
    kernel_fpu_begin();
    
    float f1 = 0;
    returnDoubleParam(&f1);
    
    float f = 0;
    float* fp = returnDouble();
    kfree(fp);
    
    kernel_fpu_end();

    return 0;
}

/*****************************************************************************/

void __exit cleanup_mini_module(void)
{
    printk(KERN_INFO "Stopping...\n");
    printk(KERN_INFO "MathDriver stopped\n");
    /*****************************************************************************/
}

/*****************************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("LPM (Martin Kraner)");
MODULE_DESCRIPTION("FDLIBM Kernel Test module");

module_init(init_mini_module);
module_exit(cleanup_mini_module);
