/*
 * Copyright (c) 2001, Paul Clarke, Hydra Electronic Design Solutions Pty Ltd.
 * http://www.hydraelectronics.com.au
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.  
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: vectors.c,v 1.2 2001/10/25 18:55:57 adam Exp $
 *
 */

///////////////////////////////////////////////////////////////////////////////
//
// Module: vectors.c
// Description:
//    Interrupt vector table for use on the H8S/2148
//
// Comments:
//  This modules defines the function that is executed when a H8 
//  exception is processed.
//

#include    "hd2144.h"

void default_irq(void) __attribute__ ((OS_Task));
void default_irq(void)
{
    __asm__ volatile ("jmp  @@0x01c");    // find addr of nmi routine and go there
}

void nmi_irq(void) __attribute__ ((interrupt_handler));
void nmi_irq(void)
{
    // use watchdog to make a reset
    h8_wdt_tcsr0_w = 0xA56f;  // cause a reset when counter overflows
    h8_wdt_tcnt0_w = 0x5aff;  // counter = 0xff
}
