/*
 *  Implementation of standard module Char.
 */


int __dummy_value_which_is_completely_useless=0;



/*
 *  There's nothing to do here because all functions are directly
 *  taken from libc.
 *
 *  Unfortunately, things are not as easy as they should be.
 *  If there is no symbol declared in this file then gcc creates an
 *  object file which does not contain any objects. This causes ranlib
 *  not (!!) to produce an empty symbol table, but to produce no symbol
 *  table at all. Finding no symbol table lets the linker give some
 *  nasty warnings. These are suppressed by the above dummy symbol.
 */
