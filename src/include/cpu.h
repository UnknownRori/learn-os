#pragma once

#ifndef RORI_CPU_H
#define RORI_CPU_H

// This function will halt any current excecution
void halt();

void interrupt_enable();
void interrupt_disable();

#endif
