/*
 * irq.h
 *
 *  Created on: 2013-5-18
 *      Author: xie
 */

#ifndef IRQ_H_
#define IRQ_H_
typedef void (*func_irq)(int number,char* argv[]);
void firefly_irq_service_entry();
void firefly_irq_service_add(int irq,func_irq irq_serverfunc);
void firefly_irq_func_del(int irq);
void irq_server(int pc);
#endif /* IRQ_H_ */
