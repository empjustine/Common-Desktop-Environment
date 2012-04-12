/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: parser.h /main/3 1995/11/08 09:41:12 rswiston $ */
/*
              Copyright 1986 Tandem Computers Incorporated.
This product and information is proprietary of Tandem Computers Incorporated.
                   Copyright 1986, 1987, 1988, 1989 Hewlett-Packard Co.
*/

/* Parser.h allocates global variables for PARSER */

#if defined(M_PARDEF)
#define M_PAREXTERN
#define M_PARINIT(a) = a
#else
#define M_PAREXTERN extern
#define M_PARINIT(a)
#endif

#include "common.h"

/* Stack of open entities and line number in each external file */
#define M_ENTLVL 16 /* Maximum number of open entities */
M_PAREXTERN M_ENTITY *m_opene[M_ENTLVL] ;
M_PAREXTERN int m_eopencnt M_PARINIT(0) ;
M_PAREXTERN void *m_sysent[M_ENTLVL + 1] ;
#define M_FIRSTLINE 1
M_PAREXTERN int m_line[M_ENTLVL + 1] M_PARINIT({M_FIRSTLINE}) ;
M_PAREXTERN int m_sysecnt M_PARINIT(0) ;

/* Possible states of a line -- no SGML characters yet processed, SGML
   characters processed but no data character or contextual end tag,
   data character or contextual end tag (i.e., end tag of a proper
   subelement) has occurred.  Note that linestat is stacked with each
   element.  If an element contains a line that
         * is neither its first nor last line
         * contains data characters within an included element
  the status of the line should be M_SOMETHING not M_DCORCET because the data
  characters belong to the inner element rather than the outer one.
  
  Also note that "M_DCORCET" originally stood for "data character or contextual
  end tag" when the Standard used the term "contextual element" to mean
  an element allowed by a model rather than an inclusion and when
  the rules for ignoring RE's referred to the occurrence of end tags of
  such elements rather than the entire elements.  Now the acronym can be
  interpreted as "data character or contextual element".
 */
#define M_NOTHING 0
#define M_SOMETHING 1
#define M_DCORCET 2

/* Definitions for parse stack. The primary data structure of PARSER
   is a stack containing one entry for each open element.  Each entry
   on the stack is described in an m_parse structure. Entries for
   element's whose content is defined by a content model have a
   pointer to a stack of open FSAs.  These FSA stacks do not describe
   the actual automata (which are coded in the data structures
   generated by BUILD, but rather the current state in the active
   automata.  An element's FSA stack will have one entry for the
   content model and an additional entry for each active and-group.
*/

typedef struct m_parse M_PARSE ;
typedef struct m_openfsa M_OPENFSA ;
typedef struct m_andlist M_ANDLIST ;

struct m_parse {
  /* Pointer to preceding entry on stack */
  M_PARSE *oldtop ;

  /* Identifier of element this entry represents */
  M_ELEMENT element ;

  /* Pointer to table of parameter pointers for this instance of this
     element */
  M_WCHAR **param ;

  /* Pointer to stack of open FSAs for this element */
  M_OPENFSA *fsastack ;

  /* For RCDATA elements to indicate the nesting level
     of entities when the element opened, since net and etago
     delimiters are not recognized except in the same entity
     as the element began. */
  int thisent ;

  /* TRUE iff the element's start-tag ended with a NET so that a NET
     is expected to end the element */
  LOGICAL neednet ;

  /* Has a Record End occurred in the element's content? */
  LOGICAL firstre ; 

  /* Flag that indicates whether the element is contextual, i.e.,
     whether it occurred because it was allowed in context by a
     content model, or it was allowed by an inclusion exception or
     occurred by error.  (The term "contextual subelement" was used
     in the Draft International Standard in the same sense as
     "proper subelement" in the International Standard.) */
  LOGICAL contextual ;

  /* Whether character data is currently being processed. */
  LOGICAL intext ;

  /* Line status.  Indicates whether anything has occurred after
     the start-tag or most recent Record Start in this element */
  char linestat ;

  /* Flag indicating whether or not a Record End (carriage return)
     has been scanned and is being held to see if there is more
     content in the element.  If there is, the RE will be processed
     as a data character, otherwise it will be discarded. */
  LOGICAL holdre ;

  /* Pointer to the element's short reference map.  The value is NULL
     if there is no map. */
  int *map ;

  /* Index in actions for processing text characters encountered
     in this element, and pointer to stack location where parameters
     should be retrieved. */
  int cdcase ;
  M_PARSE *cdparam ;

  /* Index in actions for processing processing instructions
     encountered in this element, and pointer to stack location where
     parameters should be retrieved. */
  int picase ;
  M_PARSE *piparam ;

  /* Index in actions for processing start- and end-strings
     encountered in this element, and pointer to stack location where
     parameters should be retrieved. */
  int stccase ;
  M_PARSE *stparam ;

  /* Pointer to name of input file in which the current element
    began (NULL if primary input file). */
  M_WCHAR *file ;

  /* Line number where the current element began. */
  int line ;

  /* Interface-defined pointer stored on the stack */
  void *ifdata ;
  } ;

struct m_openfsa {
  /* Pointer to preceding entry on FSA stack */
  M_OPENFSA *oldtop ;

  /* Current state in this FSA */
  M_STATE current ;

  /* Identifier of set of and-groups being processed and pointer to list of 
     and-groups that have occurred within this set. */
  M_ANDGROUP andgroup ;
  M_ANDLIST *usedand ;
  } ;

struct m_andlist {
  M_ANDGROUP group ;
  M_ANDLIST *next ;
  } ;

extern M_OPENFSA m_botfsa ;

/* Bottom marker of parse stack */
M_PAREXTERN M_PARSE m_stackbot 
#if defined(M_PARDEF)
  = {
  /* M_PARSE *oldtop ;*/           NULL,
  /* M_ELEMENT element ;*/         M_NULLVAL,
  /* M_WCHAR **param ;*/           NULL,
  /* M_OPENFSA *fsastack ;*/       &m_botfsa,
  /* int thisent ;*/               0,
  /* LOGICAL neednet ;*/           FALSE,
  /* LOGICAL firstre ; */          FALSE,
  /* LOGICAL contextual ;*/        TRUE,
  /* LOGICAL intext ;*/            FALSE,
  /* int linestat ;*/              M_NOTHING,
  /* LOGICAL holdre ;*/            FALSE,
  /* int *map ;*/                  NULL,
  /* int cdcase ;*/                1,
  /* M_PARSE *cdparam ;*/          &m_stackbot,
  /* int picase ;*/                1,
  /* M_PARSE *piparam ;*/          &m_stackbot,
  /* int stccase ;*/               1,
  /* M_PARSE *stparam ;*/          &m_stackbot,
  /* M_WCHAR *file ;*/             NULL,
  /* int line ;*/                  M_FIRSTLINE,
  /* void *ifdata ;*/              NULL,
  }
#endif
  ;

M_PAREXTERN M_OPENFSA m_botfsa
#if defined(M_PARDEF)
  = {
  /* M_OPENFSA *oldtop ;*/         NULL,
  /* M_STATE current ;*/           1,
  /* M_ANDGROUP andgroup ;*/       M_NULLVAL,
  /* M_ANDGROUP *usedand ;*/       NULL,
  }
#endif
  ;

/* Index of current top of parse stack */
M_PAREXTERN M_PARSE *m_stacktop M_PARINIT(&m_stackbot) ;

/* Pointer to stack location where parameters for current code
segment are defined.  Used for inherited code segments (text-code,
pi-code, string-code) */
M_PAREXTERN M_PARSE *m_stackpar ;

/* Type of characters */
typedef char M_HOLDTYPE ;

#if defined(M_PARDEF)
#include "chartype.h"
#else
extern M_CHARTYPE m_ctarray[M_CHARSETLEN] ;
#endif

/* Indicates a start tag is allowed by an inclusion exception */
#define M_NONCONTEXTUAL 2

/* Character used to delimit parameter names in start and end strings 
   entered as data to ELTDEF */
#define M_ESCAPECHAR '@'

/* Pointer to name of element */
#define m_nameofelt(x) &m_ename[m_element[x - 1].enptr]

/* Status of characters as read from input stream */
#define M_EE 0
#define M_NORMAL 1
#define M_CDCHAR 2
#define M_ENTNORMAL 3

/* State transition network generated by CONTEXT */
#include "sparse.h"

/* Maximum length of a sequence of blanks in a short reference delimiter */
#define M_BSEQLEN 100

/* #defines used in recognition of short reference delimiters */
#if defined(M_PARDEF)
#define M_HOLDSIZ M_MAXSR + M_BSEQLEN * M_MAXSEQ + 1
#else
#define M_HOLDSIZ
#endif
#define M_REGCHAR 1
#define M_SEQCHAR 2
#define M_BSCHAR 3
#define M_WSCHAR 4
#define M_RSCHAR 5

/* Number of allowable tokens to display after a syntax error */
#define M_EXPLIMIT 5

/* Status of T option output */
#define M_TOPTSTARTTAG 0
#define M_WHITESPACE 1
#define M_OTHER 2

/* Maximum length of processing instruction (not in a PI entity) */
#define M_PILEN 240

/* Storage for a name token just read by the scanner; and for a name read
   while parsing parameters */
M_PAREXTERN M_WCHAR m_name[M_NAMELEN + 1] ;
M_PAREXTERN M_WCHAR m_saveatt[M_NAMELEN + 1] ;

/* M_curcon is current state of FSA that controls parser; m_prevcon is the
   value of m_curcon before last character was scanned; m_token is the token
   type returned by last call to scanner; and
   m_scanval is index of element name just read within tag delimiters */
M_PAREXTERN int m_curcon M_PARINIT(PROLOG) ;
M_PAREXTERN int m_prevcon ;
M_PAREXTERN int m_token ;
M_PAREXTERN int m_scanval ;

char *user_defined_entities M_PARINIT("USER-DEFINED-ENTITIES");

/* Declarations for tentative list of omitted tags when checking for tag
   MINimization */
typedef struct m_min M_MIN ;
struct m_min {
  int val ;
  M_MIN *next ;
  } ;
M_PAREXTERN M_MIN *m_minstart ;
M_PAREXTERN M_MIN *m_minend ;
M_PAREXTERN M_MIN **m_nextms ;
M_PAREXTERN M_MIN **m_nextme ;

/* Count of the number of open elements expecting to be terminated with
   a NET */
M_PAREXTERN int m_netlevel M_PARINIT(0) ;

/* Count of errors that have occurred */
M_PAREXTERN int m_errcnt M_PARINIT(0) ;
#define M_ERRLIM 100
M_PAREXTERN int m_errlim M_PARINIT(M_ERRLIM) ;
M_PAREXTERN int m_expcount ;
M_PAREXTERN LOGICAL m_errexit M_PARINIT(FALSE) ;

/* Flag to indicate whether processing of the text has begun */
M_PAREXTERN LOGICAL m_start M_PARINIT(FALSE) ;

/* Flag indicates whether current start tag is terminated by End-tag
   indicator or by tag-close delimiter (or start of another tag) */
M_PAREXTERN LOGICAL m_scannet ;

/* Storage for literals */
M_PAREXTERN M_WCHAR m_literal[M_LITLEN + 1] ;

/* Buffer for sequence of white space that has been read before it is
   determined whether or not the white space is significant */
#define M_WSPACELEN 100
M_PAREXTERN int m_wspace[M_WSPACELEN] ;
M_PAREXTERN int m_wscount M_PARINIT(0) ;
M_PAREXTERN int m_maxws M_PARINIT(0) ;
M_PAREXTERN int m_wsused ;

/* Temporary pointers to parameter values.  Used while scanning start tag
   before element is placed on parse stack.*/
M_PAREXTERN
#if defined M_PROTO
#endif
M_WCHAR *m_poccur[
#if defined(M_PARDEF)
M_MAXPAR ? M_MAXPAR : 1
#endif
] ;

/* Index of a particular parameter within the parameter list for a given
   element */
M_PAREXTERN int m_psave ;
/* Index of a particular parameter within the list of all parameters for all
   elements */
M_PAREXTERN int m_ppsave ;

/* Index of element of tag just scanned; may be result of short tag
   minimization */
M_PAREXTERN M_ELEMENT m_scanel ;

/* Read-ahead buffer and number of characters currently in that buffer */
#define M_SAVECHAR 500
M_PAREXTERN int m_savechar[M_SAVECHAR] ;
M_PAREXTERN M_WCHAR m_savedchar[M_SAVECHAR] ;
M_PAREXTERN M_WCHAR m_oldlinestat[M_SAVECHAR] ;
M_PAREXTERN M_WCHAR m_oldatrs[M_SAVECHAR] ;
M_PAREXTERN int m_sourcefile[M_SAVECHAR] ;
M_PAREXTERN M_WCHAR m_atrs M_PARINIT(TRUE) ;
M_PAREXTERN int m_oldlsindex M_PARINIT(M_SAVECHAR - 1) ;
M_PAREXTERN int m_toundo M_PARINIT(0) ;
M_PAREXTERN int m_maxundo M_PARINIT(0) ;
#define M_LINELENGTH 80
M_PAREXTERN int m_saveline[M_LINELENGTH][M_ENTLVL + 1] ;
M_PAREXTERN int m_svlncnt[M_ENTLVL + 1] M_PARINIT({0}) ;
M_PAREXTERN LOGICAL m_svlnwrap[M_ENTLVL + 1] M_PARINIT({FALSE}) ;

/* Arrays used for short references */
M_PAREXTERN int m_hold[M_HOLDSIZ] ;
M_PAREXTERN M_HOLDTYPE m_dhold[M_HOLDSIZ] ;
M_PAREXTERN int m_delim[M_HOLDSIZ] ;
M_PAREXTERN char m_srefchartype[M_HOLDSIZ] ;
M_PAREXTERN int m_current[M_HOLDSIZ] ;

/* Options
      A -- Trace of calls to m_malloc() and m_free()
      B -- 
      C -- Trace of calls to m_getachar(), putachar()
      D -- Trace of encountered data characters
      E -- Don't report duplicate entity declarations
      F -- 
      G -- 
      H -- M_malloc and m_free check for valid heap
      I -- 
      J -- 
      K -- 
      L -- Don't limit number of possible tokens displayed by expecting()
      M -- Determine start-tag minimization strictly according to the Standard
      N -- 
      O -- 
      P -- 
      Q -- 
      R -- 
      S -- Scanner trace
      T -- Tag trace
      U -- 
      V -- 
      W -- Missing tagc not considered an error
      X -- 
      Y -- 
      Z -- 
*/

M_PAREXTERN LOGICAL m_malftrace M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_chtrace M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_cdtrace M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_entdupchk M_PARINIT(TRUE) ;
M_PAREXTERN LOGICAL m_heapchk M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_explimit M_PARINIT(TRUE) ;
M_PAREXTERN LOGICAL m_conform M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_scantrace M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_tagtrace M_PARINIT(FALSE) ;
M_PAREXTERN LOGICAL m_wholetag M_PARINIT(FALSE) ;
M_PAREXTERN int m_toptstat ;

/* Flag that indicates when unexpected content detected after document
   appears to be complete */
M_PAREXTERN LOGICAL m_aftereod M_PARINIT(FALSE) ;

/* Save standard C main program arguments */
M_PAREXTERN int m_argc ;
M_PAREXTERN char **m_argv ;

/* PARSER output file */
#if defined(linux)
M_PAREXTERN FILE *m_outfile;
M_PAREXTERN FILE *m_errfile;
#else
M_PAREXTERN FILE *m_outfile M_PARINIT(stdout) ;
M_PAREXTERN FILE *m_errfile M_PARINIT(stdout) ;
#endif

/* Save processing instruction */
M_PAREXTERN M_WCHAR m_pi[M_PILEN + 1] ;
M_PAREXTERN int m_pilen M_PARINIT(0) ;

/* Entity being defined */
M_PAREXTERN M_ENTITY *m_entity ;
M_PAREXTERN int m_entclen ;
M_PAREXTERN M_WCHAR m_entcontent[M_LITLEN + 1] ;

/* Largest positive integer */
#define M_BIGINT 0x7FFF

/* Include function prototypes */
#include "proto.h"

