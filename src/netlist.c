/* File: netlist.c
 *
 * This file is part of XSCHEM,
 * a schematic capture and Spice/Vhdl/Verilog netlisting tool for circuit
 * simulation.
 * Copyright (C) 1998-2022 Stefan Frederik Schippers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "xschem.h"

static int for_netlist = 0;
static void instdelete(int n, int x, int y)
{
  Instentry *saveptr, **prevptr;

  prevptr = &xctx->inst_spatial_table[x][y];
  while( (*prevptr)->n != n) prevptr = &(*prevptr)->next;
  saveptr = (*prevptr)->next;
  my_free(821, prevptr);
  *prevptr = saveptr;
}

static void instinsert(int n, int x, int y)
{
  Instentry *ptr, *newptr;
  ptr=xctx->inst_spatial_table[x][y];
  newptr=my_malloc(236, sizeof(Instentry));
  newptr->next=ptr;
  newptr->n=n;
  xctx->inst_spatial_table[x][y]=newptr;
  dbg(2, "instinsert(): inserting object %d at %d,%d\n",n,x,y);
}

static Instentry *delinstentry(Instentry *t)
{
  Instentry *tmp;
  while( t ) {
    tmp = t->next;
    my_free(822, &t);
    t = tmp;
  }
  return NULL;
}

void del_inst_table(void)
{
  int i,j;

  for(i=0;i<NBOXES;i++)
    for(j=0;j<NBOXES;j++)
      xctx->inst_spatial_table[i][j] = delinstentry(xctx->inst_spatial_table[i][j]);
  xctx->prep_hash_inst=0;
  dbg(1, "del_inst_table(): cleared object hash table\n");
}

/* what:
 * 0, XINSERT : add to hash
 * 1, XDELETE : remove from hash
 */
void hash_inst(int what, int n) /* 20171203 insert object bbox in spatial hash table */
{
  int tmpi,tmpj, counti,countj,i,j;
  double tmpd;
  double x1, y1, x2, y2;
  int x1a, x2a, y1a, y2a;

  x1=xctx->inst[n].x1;
  x2=xctx->inst[n].x2;
  y1=xctx->inst[n].y1;
  y2=xctx->inst[n].y2;
  /* ordered bbox */
  if( x2 < x1) { tmpd=x2;x2=x1;x1=tmpd;}
  if( y2 < y1) { tmpd=y2;y2=y1;y1=tmpd;}

  /* calculate square 4 1st bbox point of object[k] */
  x1a=(int)floor(x1/BOXSIZE);
  y1a=(int)floor(y1/BOXSIZE);

  /* calculate square 4 2nd bbox point of object[k] */
  x2a=(int)floor(x2/BOXSIZE);
  y2a=(int)floor(y2/BOXSIZE);

  /*loop thru all squares that intersect bbox of object[k] */
  counti=0;
  for(i=x1a; i<=x2a && counti < NBOXES; i++)
  {
   counti++;
   tmpi=i%NBOXES; if(tmpi<0) tmpi+=NBOXES;
   countj=0;
   for(j=y1a; j<=y2a && countj < NBOXES; j++)
   {
    countj++;
    tmpj=j%NBOXES; if(tmpj<0) tmpj+=NBOXES;
    /* insert object_ptr[n] in region [tmpi, tmpj] */
    if(what == XINSERT) instinsert(n, tmpi, tmpj);
    else instdelete(n, tmpi, tmpj);
   }
  }
}
void hash_instances(void) /* 20171203 insert object bbox in spatial hash table */
{
 int n;

 if(xctx->prep_hash_inst) return;
 del_inst_table();
 for(n=0; n<xctx->instances; n++) {
   hash_inst(XINSERT, n);
 }
 xctx->prep_hash_inst=1;
}

static void instpindelete(int n,int pin, int x, int y)
{
  Instpinentry *saveptr, **prevptr, *ptr;

  prevptr = &xctx->instpin_spatial_table[x][y];
  ptr = *prevptr;
  while(ptr) {
    if(ptr->n == n && ptr->pin == pin) {
      saveptr = ptr->next;
      my_free(823, &ptr);
      *prevptr = saveptr;
      return;
    }
    prevptr = &ptr->next;
    ptr = *prevptr;
  }
}

/*                                      --pin coordinates--  -square coord- */
static void instpininsert(int n,int pin, double x0, double y0, int x, int y)
{
 Instpinentry *ptr, *newptr;

 ptr=xctx->instpin_spatial_table[x][y];
 newptr=my_malloc(237, sizeof(Instpinentry));
 newptr->next=ptr;
 newptr->n=n;
 newptr->x0=x0;
 newptr->y0=y0;
 newptr->pin=pin;
 xctx->instpin_spatial_table[x][y]=newptr;
 dbg(2, "instpininsert(): inserting inst %d at %d,%d\n",n,x,y);
}


static Instpinentry *delinstpinentry(Instpinentry *t)
{
  Instpinentry *tmp;

  while(t) {
    tmp = t->next;
    my_free(824, &t);
    t = tmp;
  }
  return NULL;
}

static void del_inst_pin_table(void)
{
 int i,j;

 for(i=0;i<NBOXES;i++)
  for(j=0;j<NBOXES;j++)
   xctx->instpin_spatial_table[i][j] = delinstpinentry(xctx->instpin_spatial_table[i][j]);
}


static void wiredelete(int n, int x, int y)
{
  Wireentry *saveptr, **prevptr;

  prevptr = &xctx->wire_spatial_table[x][y];
  while( (*prevptr)->n != n) prevptr = &(*prevptr)->next;
  saveptr = (*prevptr)->next;
  my_free(825, prevptr);
  *prevptr = saveptr;
}

static void wireinsert(int n, int x, int y)
{
  Wireentry *ptr, *newptr;

  ptr=xctx->wire_spatial_table[x][y];
  newptr=my_malloc(238, sizeof(Wireentry));
  newptr->next=ptr;
  newptr->n=n;
  xctx->wire_spatial_table[x][y]=newptr;
  dbg(2, "wireinsert(): inserting wire %d at %d,%d\n",n,x,y);
}

static Wireentry *delwireentry(Wireentry *t)
{
  Wireentry *tmp;

  while( t ) {
    tmp = t->next;
    my_free(826, &t);
    t = tmp;
  }
  return NULL;
}

void del_wire_table(void)
{
 int i,j;

 for(i=0;i<NBOXES;i++)
  for(j=0;j<NBOXES;j++)
   xctx->wire_spatial_table[i][j] = delwireentry(xctx->wire_spatial_table[i][j]);
 xctx->prep_hash_wires=0;
}

void get_square(double x, double y, int *xx, int *yy)
{
 int xa, xb, ya, yb;

 xa=(int)floor(x/BOXSIZE) ;
 xb=xa % NBOXES; if(xb<0) xb+=NBOXES;
 ya=(int)floor(y/BOXSIZE) ;
 yb=ya % NBOXES; if(yb<0) yb+=NBOXES;

 *xx=xb;
 *yy=yb;
}

/* what:
 * 0, XINSERT : add to hash
 * 1, XDELETE : remove from hash
 */
static void hash_inst_pin(int what, int i, int j)
/*                                                    inst   pin */

{
  xRect *rct;
  char *prop_ptr;
  double x0, y0, rx1, ry1;
  short rot, flip;
  int sqx, sqy;
  int rects;

  rects=(xctx->inst[i].ptr+ xctx->sym)->rects[PINLAYER] ;
  if(j>=rects)  /* generic pins */
  {
    rct=(xctx->inst[i].ptr+ xctx->sym)->rect[GENERICLAYER];
    x0=(rct[j-rects].x1+rct[j-rects].x2)/2;
    y0=(rct[j-rects].y1+rct[j-rects].y2)/2;
    prop_ptr = rct[j-rects].prop_ptr;
  }
  else
  {
    rct=(xctx->inst[i].ptr+ xctx->sym)->rect[PINLAYER];
    x0=(rct[j].x1+rct[j].x2)/2;
    y0=(rct[j].y1+rct[j].y2)/2;
    prop_ptr = rct[j].prop_ptr;
  }


  if(for_netlist && j<rects &&
     (!prop_ptr || !get_tok_value(prop_ptr, "name",0)[0] || !get_tok_value(prop_ptr, "dir",0)[0]) ) {
    char str[2048];
    my_snprintf(str, S(str), "symbol %s: missing all or name or dir attributes on pin %d\n  %s",
        xctx->inst[i].name, j, prop_ptr);
    statusmsg(str,2);
    tcleval("show_infotext"); /* critical error: force ERC window showing */
    if(!xctx->netlist_count) {
      xctx->inst[i].color = -PINLAYER;
      xctx->hilight_nets=1;
    }
  }
  rot=xctx->inst[i].rot;
  flip=xctx->inst[i].flip;
  ROTATION(rot, flip, 0.0,0.0,x0,y0,rx1,ry1);
  x0=xctx->inst[i].x0+rx1;
  y0=xctx->inst[i].y0+ry1;
  get_square(x0, y0, &sqx, &sqy);
  if( what == XINSERT ) instpininsert(i, j, x0, y0, sqx, sqy);
  else                 instpindelete(i, j, sqx, sqy);
}

/* what:
 * 0, XINSERT : add to hash
 * 1, XDELETE : remove from hash
 */
void hash_wire(int what, int n, int incremental)
{
  int tmpi,tmpj, counti,countj,i,j;
  double tmpd;
  double x1, y1, x2, y2;
  int x1a, x2a, y1a, y2a;
  Wireentry *wptr;
  xWire * const wire = xctx->wire;

  wire[n].end1 = wire[n].end2=-1;
  x1=wire[n].x1;
  x2=wire[n].x2;
  y1=wire[n].y1;
  y2=wire[n].y2;
  /* ordered bbox */
  if( x2 < x1) { tmpd=x2;x2=x1;x1=tmpd;}
  if( y2 < y1) { tmpd=y2;y2=y1;y1=tmpd;}

  /* calculate square 4 1st bbox point of wire[k] */
  x1a=(int)floor(x1/BOXSIZE) ;
  y1a=(int)floor(y1/BOXSIZE) ;

  /* calculate square 4 2nd bbox point of wire[k] */
  x2a=(int)floor(x2/BOXSIZE);
  y2a=(int)floor(y2/BOXSIZE);

  /*loop thru all squares that intersect bbox of wire[k] */
  counti=0;
  for(i=x1a; i<=x2a && counti < NBOXES; i++)
  {
   counti++;
   tmpi=i%NBOXES; if(tmpi<0) tmpi+=NBOXES;
   countj=0;
   for(j=y1a; j<=y2a && countj < NBOXES; j++)
   {
    countj++;
    tmpj=j%NBOXES; if(tmpj<0) tmpj+=NBOXES;
    /* insert wire[n] in region [tmpi, tmpj] */
    if(what==XINSERT) wireinsert(n, tmpi, tmpj);
    else  wiredelete(n, tmpi, tmpj);

    /* reset ends of all wires that *could* touch wire[n] */
    if(incremental) for(wptr = xctx->wire_spatial_table[tmpi][tmpj] ; wptr ; wptr = wptr->next) {
      wire[wptr->n].end1 = wire[wptr->n].end2 = -1;
    }
   }
  }
}

void hash_wires(void)
{
 int n;
 if(xctx->prep_hash_wires) return;
 del_wire_table();

 for(n=0; n<xctx->wires; n++) hash_wire(XINSERT, n, 0);
 xctx->prep_hash_wires=1;
}

/* return 0 if library path of s matches any lib name in tcl variable $xschem_libs */
/* what: 
 * 1: netlist exclude pattern
 * 2: hierarchical print exclude pattern
 * 4: hierarchical cell listing exclude pattern 
 */
int check_lib(int what, const char *s)
{
 int range,i, found;
 char str[PATH_MAX + 512]; /* overflow safe 20161122 */

 found=0;
 if(what & 1) tcleval("llength $xschem_libs");
 if(what & 2) tcleval("llength $noprint_libs");
 if(what & 4) tcleval("llength $nolist_libs");
 range = atoi(tclresult());
 dbg(1, "check_lib(): s=%s, range=%d\n", s, range);

 for(i=0;i<range;i++){
  if(what & 1 ) my_snprintf(str, S(str), "lindex $xschem_libs %d",i);
  if(what & 2 ) my_snprintf(str, S(str), "lindex $noprint_libs %d",i);
  if(what & 4 ) my_snprintf(str, S(str), "lindex $nolist_libs %d",i);
  tcleval(str);
  dbg(1, "check_lib(): %s -> %s\n", str, tclresult());
  my_snprintf(str, S(str), "regexp {%s} {%s}", tclresult(), s);
  dbg(1, "check_lib(): str=%s\n", str);
  tcleval(str);
  if( tclresult()[0] == '1') found=1;
 }
 if(found) return 0;
 else return 1;
}

void netlist_options(int i)
{
  const char * str;
  str = get_tok_value(xctx->inst[i].prop_ptr, "bus_replacement_char", 0);
  if(str[0] && str[1] && strlen(str) ==2) {
    bus_char[0] = str[0];
    bus_char[1] = str[1];
    /* tclsetvar("bus_replacement_char", str); */
  }
  /* fprintf(errfp, "netlist_options(): bus_char=%s\n", str); */

  str = get_tok_value(xctx->inst[i].prop_ptr, "top_subckt", 0);
  if(str[0]) {
    /* fprintf(errfp, "netlist_options(): prop_ptr=%s\n", xctx->inst[i].prop_ptr); */
    if(!strcmp(str, "true")) tclsetintvar("top_subckt", 1);
    else tclsetintvar("top_subckt", 0);
  }
  str = get_tok_value(xctx->inst[i].prop_ptr, "spiceprefix", 0);
  if(str[0]) {
    /* fprintf(errfp, "netlist_options(): prop_ptr=%s\n", xctx->inst[i].prop_ptr); */
    if(!strcmp(str, "false")) tclsetvar("spiceprefix", "0");
    else tclsetvar("spiceprefix", "1");
  }

  str = get_tok_value(xctx->inst[i].prop_ptr, "hiersep", 0);
  if(str[0]) {
    my_snprintf(xctx->hiersep, S(xctx->hiersep), "%s", str);
  }
}

void set_tcl_netlist_type(void)
{
    if(xctx->netlist_type == CAD_SPICE_NETLIST) {
      tclsetvar("netlist_type", "spice");
    }  else if(xctx->netlist_type == CAD_VERILOG_NETLIST) {
      tclsetvar("netlist_type", "verilog");
    } else if(xctx->netlist_type == CAD_VHDL_NETLIST) {
      tclsetvar("netlist_type", "vhdl");
    } else if(xctx->netlist_type == CAD_TEDAX_NETLIST) {
      tclsetvar("netlist_type", "tedax");
    } else if(xctx->netlist_type == CAD_SYMBOL_ATTRS) {
      tclsetvar("netlist_type", "symbol");
    } else {
      tclsetvar("netlist_type", "unknown");
    }
}

/* used only for debug */
#if 0
static void print_wires(void)
{
 int i,j;
 Wireentry *ptr;
 for(i=0;i<NBOXES;i++) {
   for(j=0;j<NBOXES;j++)
   {
    dbg(1, "print_wires(): %4d%4d :\n",i,j);
    ptr=xctx->wire_spatial_table[i][j];
    while(ptr)
    {
     dbg(1, "print_wires(): %6d\n", ptr->n);
     ptr=ptr->next;
    }
    dbg(1, "print_wires(): \n");
   }
 }
 ptr=xctx->wire_spatial_table[0][1];
 while(ptr)
 {
  select_wire(ptr->n,SELECTED, 1);
  rebuild_selected_array();
  ptr=ptr->next;
 }
 draw();
}
#endif

/* store list of global nodes (global=1 set in symbol props) to be printed in netlist 28032003 */
/* what: */
/*      0: print list of global nodes and delete list */
/*      1: add entry */
/*      2: delete list only, no print */
/*      3: look if node is a global */
int record_global_node(int what, FILE *fp, char *node)
{
 static int max_globals=0; /* safe to keep even with multiple schematics, netlist code always resets data */
 static int size_globals=0; /* safe to keep even with multiple schematics, netlist code always resets data */
 static char **globals=NULL; /* safe to keep even with multiple schematics, netlist code always resets data */
 int i;

 if( what==1 || what==3) {
    if(!node) return 0;
    if(!strcmp(node, "0")) return 1;
    for(i=0;i<max_globals;i++) {
      if( !strcmp(node, globals[i] )) return 1; /* node is a global */
    }
    if(what == 3) return 0; /* node is not a global */
    if(max_globals>=size_globals) {
       size_globals+=CADCHUNKALLOC;
       my_realloc(243, &globals, size_globals*sizeof(char *) );
    }
    globals[max_globals]=NULL;
    my_strdup(244, &globals[max_globals], node);
    max_globals++;
 } else if(what == 0 || what == 2) {
    for(i=0;i<max_globals;i++) {
       if(what == 0 && xctx->netlist_type == CAD_SPICE_NETLIST) fprintf(fp, ".GLOBAL %s\n", globals[i]);
       if(what == 0 && xctx->netlist_type == CAD_TEDAX_NETLIST) fprintf(fp, "__GLOBAL__ %s\n", globals[i]);
       my_free(829, &globals[i]);
    }
    my_free(830, &globals);
    size_globals=max_globals=0;
 }
 return 0;
}

void get_inst_pin_coord(int i, int j, double *x, double *y)
{
  xRect *rct;
  int rects, rot, flip;
  double x0, y0, rx1, ry1;
  xInstance * const inst = xctx->inst;
  rects = (inst[i].ptr+ xctx->sym)->rects[PINLAYER];
  if(j < rects) {
    rct=(inst[i].ptr+ xctx->sym)->rect[PINLAYER];
    x0=(rct[j].x1+rct[j].x2)/2;
    y0=(rct[j].y1+rct[j].y2)/2;
    rot=inst[i].rot;
    flip=inst[i].flip;
    ROTATION(rot, flip, 0.0,0.0,x0,y0,rx1,ry1);
    *x=inst[i].x0+rx1;
    *y=inst[i].y0+ry1;
  } else {
    *x = 0;
    *y = 0;
  }
}

/* what==0 -> initialize  */
/* what==1 -> get new node name, net##   */
/* what==2 -> update multiplicity   */
/* what==3 -> get node multiplicity */
int get_unnamed_node(int what, int mult,int node)
{
  dbg(2, "get_unnamed_node(): what=%d mult=%d node=%d\n", what, mult, node);
  if(what==0) { /* initialize unnamed node data structures */
    xctx->new_node=0;
    my_free(828, &xctx->node_mult);
    xctx->node_mult_size=0;
    return 0;
  }
  else if(what==1) { /* get a new unique unnamed node */
    char tmp_str[30];
    do {
      ++xctx->new_node;
      my_snprintf(tmp_str, S(tmp_str), "net%d", xctx->new_node);
    /* JL avoid autonamed nets clash with user defined 'net#' names */
    } while (bus_node_hash_lookup(tmp_str, "", XLOOKUP, 0, "", "", "", "")!=NULL);
    if(xctx->new_node >= xctx->node_mult_size) { /* enlarge array and zero it */
      int oldsize = xctx->node_mult_size;
      xctx->node_mult_size = xctx->new_node + CADCHUNKALLOC;
      my_realloc(242, &xctx->node_mult, sizeof(xctx->node_mult[0]) * xctx->node_mult_size );
      memset(xctx->node_mult + oldsize, 0, (xctx->node_mult_size - oldsize) * sizeof(xctx->node_mult[0]));
    }
    xctx->node_mult[xctx->new_node]=mult;
    return xctx->new_node;
  }
  else if(what==2) { /* update node multiplicity if given mult is lower */
    if(xctx->node_mult[node]==0) xctx->node_mult[node]=mult;
    else if(mult < xctx->node_mult[node]) xctx->node_mult[node]=mult;
    return 0;
  }
  else { /* what=3 , return node multiplicity */
    dbg(2, "get_unnamed_node(): returning mult=%d\n", xctx->node_mult[node]);
    return xctx->node_mult[node];
  }
}

static void name_generics()
{
  xRect *rct;
  double x0, y0;
  short rot = 0;
  short flip = 0;
  int sqx, sqy;
  double rx1,ry1;
  Instpinentry *iptr;
  int i,j, rects, generic_rects;
  char *type=NULL;
  char *sig_type=NULL;
  xInstance * const inst = xctx->inst;
  int const instances = xctx->instances;

  /* name generic pins from attached labels */
  dbg(2, "prepare_netlist_structs(): naming generics from attached labels\n");
  if(for_netlist) for (i=0;i<instances;i++) { /* ... assign node fields on all (non label) instances */
    if(inst[i].ptr<0) continue;
    my_strdup(267, &type,(inst[i].ptr+ xctx->sym)->type);
    if(type && !IS_LABEL_OR_PIN(type) ) {
      if((generic_rects = (inst[i].ptr+ xctx->sym)->rects[GENERICLAYER]) > 0) {
        rects = (inst[i].ptr+ xctx->sym)->rects[PINLAYER];
        for (j=rects;j<rects+generic_rects;j++) {
          if(inst[i].node[j]) continue; /* already named node */
          rct=(inst[i].ptr+ xctx->sym)->rect[GENERICLAYER];
          x0=(rct[j-rects].x1+rct[j-rects].x2)/2;
          y0=(rct[j-rects].y1+rct[j-rects].y2)/2;
          rot=inst[i].rot;
          flip=inst[i].flip;
          ROTATION(rot, flip, 0.0,0.0,x0,y0,rx1,ry1);
          x0=inst[i].x0+rx1;
          y0=inst[i].y0+ry1;
          get_square(x0, y0, &sqx, &sqy);

          for(iptr=xctx->instpin_spatial_table[sqx][sqy]; iptr; iptr = iptr ->next) {
            int p = iptr->pin;
            int n = iptr->n;
            if(n == i) continue;
            if((iptr->x0==x0) && (iptr->y0==y0)) {
              if((inst[n].ptr+ xctx->sym)->type && inst[n].node[p] != NULL &&
                 !strcmp((inst[n].ptr+ xctx->sym)->type, "label")) {
                dbg(2, "prepare_netlist_structs(): naming generic %s\n", inst[n].node[p]);
                my_strdup(268,  &inst[i].node[j], get_tok_value(inst[n].prop_ptr,"value",0) );
                if(!for_netlist) {
                  my_strdup(270, &sig_type,"");
                  bus_node_hash_lookup(inst[n].node[p],"", XINSERT, 1, sig_type,"", "","");
                } else {
                  my_strdup(271, &sig_type,get_tok_value(
                    (inst[i].ptr+ xctx->sym)->rect[GENERICLAYER][j-rects].prop_ptr, "sig_type",0));
                  /* insert generic label in hash table as a port so it will not */
                  /* be declared as a signal in the vhdl netlist. this is a workaround */
                  /* that should be fixed 25092001 */
                  bus_node_hash_lookup(inst[n].node[p],
                    get_tok_value((inst[i].ptr+ xctx->sym)->rect[GENERICLAYER][j-rects].prop_ptr, "dir",0),
                    XINSERT, 1, sig_type,"", "","");
                }
              } /* end if(inst[iptr->n].node[iptr->pin] != NULL) */
            } /* end if( (iptr->x0==x0) && (iptr->y0==y0) ) */
          } /* end for(iptr=xctx->instpin_spatial_table[sqx][sqy]; iptr; iptr = iptr ->next) */
        } /* end for(j=0;j<rects;j++) */
      } /* end if( rects=...>0) */
    } /* end if(type not a label nor pin)... */
  } /* end for(i...) */
  if(type) my_free(973, &type);
}

static void signal_short( const char *tag, const char *n1, const char *n2)
{
 char str[2048];
 if( n1 && n2 && strcmp( n1, n2) )
 {
   my_snprintf(str, S(str), "%s shorted: %s - %s", tag, n1, n2);
   dbg(1, "signal_short(): signal_short: shorted: %s - %s", n1, n2);
   statusmsg(str,2);
   tcleval("show_infotext"); /* critical error: force ERC window showing */
   if(!xctx->netlist_count) {
      bus_hilight_hash_lookup(n1, xctx->hilight_color, XINSERT);
      if(tclgetboolvar("incr_hilight")) incr_hilight_color();
      bus_hilight_hash_lookup(n2, xctx->hilight_color, XINSERT);
      if(tclgetboolvar("incr_hilight")) incr_hilight_color();
   }
 }
}

static void set_inst_node(int i, int j, const char *node)
{
  xInstance * const inst = xctx->inst;
  int inst_mult;
  xRect *rect = (inst[i].ptr + xctx->sym)->rect[PINLAYER];

  dbg(1, "set_inst_node(): inst %s pin %d <-- %s\n", inst[i].instname, j, node);
  expandlabel(inst[i].instname, &inst_mult);
  my_strdup(275,  &inst[i].node[j], node);
  if(!for_netlist) {
    bus_node_hash_lookup(inst[i].node[j],"", XINSERT, 0,"","","","");
  } else {
    const char *dir = get_tok_value(rect[j].prop_ptr, "dir",0);
    bus_node_hash_lookup(inst[i].node[j], dir, XINSERT, 0,"","","","");
  }
  if(node[0] == '#') { /* update multilicity of unnamed node */
    int pin_mult; 
    expandlabel(get_tok_value(rect[j].prop_ptr, "name", 0), &pin_mult);
    get_unnamed_node(2, pin_mult * inst_mult, atoi((inst[i].node[j]) + 4));
  }
}

static void instcheck(int n, int p);

static void name_attached_inst_to_net(int k, int sqx, int sqy)
{       
  xInstance * const inst = xctx->inst;
  xWire * const wire = xctx->wire;
  Instpinentry *iptr;
  for(iptr = xctx->instpin_spatial_table[sqx][sqy]; iptr; iptr = iptr->next) {
    int n = iptr->n;
    int p = iptr->pin;
    double x0 = iptr->x0;
    double y0 = iptr->y0;
    int rects=(inst[n].ptr+ xctx->sym)->rects[PINLAYER];
    if(p >= rects) continue; /* generic pins are handled in name_generics() */
    if(!inst[n].node) continue;
    if(touch(wire[k].x1, wire[k].y1, wire[k].x2, wire[k].y2, x0, y0)) {
      if(!inst[n].node[p]) {
        dbg(1, "name_attached_inst_to_net(): inst %s, pin %d <-- %s\n", 
              inst[n].instname, p, wire[k].node);
        set_inst_node(n, p, wire[k].node);
        instcheck(n, p);
      } else {
        if(for_netlist>0) signal_short("net to named instance pin", wire[k].node, inst[n].node[p]);
      }
    }
  }     
}

static void wirecheck(int k)    /* recursive routine */
{
  int tmpi, tmpj, counti, countj, i, j, touches, x1a, x2a, y1a, y2a;
  double x1, y1, x2, y2;
  Wireentry *wptr;
  xWire * const wire = xctx->wire;
 
  x1 = wire[k].x1; y1 = wire[k].y1;
  x2 = wire[k].x2; y2 = wire[k].y2;
  /* ordered bbox */
  RECTORDER(x1, y1, x2, y2);
  /* calculate square 4 1st bbox point of wire[k] */
  x1a = (int)floor(x1 / BOXSIZE);
  y1a = (int)floor(y1 / BOXSIZE);
  /* calculate square 4 2nd bbox point of wire[k] */
  x2a = (int)floor(x2 / BOXSIZE);
  y2a = (int)floor(y2 / BOXSIZE);
  /*loop thru all squares that intersect bbox of wire[k] */
  counti = 0;
  for(i = x1a; i <= x2a && counti < NBOXES; i++) {
    counti++;
    tmpi = i % NBOXES; if(tmpi < 0) tmpi += NBOXES;
    countj = 0;
    for(j = y1a; j <= y2a && countj < NBOXES; j++) {
      countj++;
      tmpj = j % NBOXES; if(tmpj < 0) tmpj += NBOXES;
      /*check if wire[k]  touches wires in square [tmpi, tmpj] */
      for(wptr = xctx->wire_spatial_table[tmpi][tmpj]; wptr; wptr = wptr->next) {
        int n = wptr->n;
        if(n == k) { /* itself */
          name_attached_inst_to_net(k, tmpi, tmpj);
          continue;
        } 
        touches = 
          touch(wire[k].x1, wire[k].y1, wire[k].x2, wire[k].y2, wire[n].x1, wire[n].y1) ||
          touch(wire[k].x1, wire[k].y1, wire[k].x2, wire[k].y2, wire[n].x2, wire[n].y2) ||
          touch(wire[n].x1, wire[n].y1, wire[n].x2, wire[n].y2, wire[k].x1, wire[k].y1) ||
          touch(wire[n].x1, wire[n].y1, wire[n].x2, wire[n].y2, wire[k].x2, wire[k].y2);
        if( touches ) {
          if(!wire[n].node) {
            my_strdup(239, &wire[n].node, wire[k].node);
            my_strdup(240, &wire[n].prop_ptr, subst_token(wire[n].prop_ptr, "lab", wire[n].node));
            name_attached_inst_to_net(n, tmpi, tmpj);
            wirecheck(n); /* recursive check */
          } else {
            if(for_netlist>0) signal_short("Net to net", wire[n].node, wire[k].node);
          }
        }
      }
    }
  }
}

static void name_attached_nets(double x0, double y0, int sqx, int sqy, const char *node)
{
  xWire * const wire = xctx->wire;
  Wireentry *wptr;
  for(wptr = xctx->wire_spatial_table[sqx][sqy]; wptr; wptr = wptr->next) {
    int n = wptr->n;
    if(touch(wire[n].x1, wire[n].y1, wire[n].x2, wire[n].y2, x0,y0)) {
      if(!wire[n].node) {
        my_strdup(263,  &wire[n].node, node);
        my_strdup(264, &wire[n].prop_ptr, subst_token(wire[n].prop_ptr, "lab", wire[n].node));
        wirecheck(n);
      } else {
        if(for_netlist>0) signal_short("Net", wire[n].node, node);
      }
    }
   
  }
}

static void name_attached_inst(int i, double x0, double y0, int sqx, int sqy, const char *node)
{     
  xInstance * const inst = xctx->inst;
  Instpinentry *iptr;
  for(iptr = xctx->instpin_spatial_table[sqx][sqy]; iptr; iptr = iptr->next) {
    int n = iptr->n;
    int p = iptr->pin;
    int rects=(inst[n].ptr+ xctx->sym)->rects[PINLAYER];
    if(i == n) continue; /* itself -> skip */
    if(p >= rects) continue; /* generic pins are handled in name_generics() */
    if(!inst[n].node) continue;
    if(iptr->x0 == x0 && iptr->y0 == y0 ) {
      if(!inst[n].node[p]) {
        set_inst_node(n, p, node);
        instcheck(n, p);
      } else {
        if(for_netlist>0) signal_short("Instance pin", inst[n].node[p], node);
      }
    }

  }
}

/* what: 
 * Determine if given "ninst" instance has pass-through pins 
 * 0: initialize
 * 1: query
 * 2: cleanup
 */
static int find_pass_through_symbols(int what, int ninst)
{
  int i, j, k;
  xInstance * const inst = xctx->inst;
  int const instances = xctx->instances;
  Int_hashtable table = {NULL, 0};
  static int *pt_symbol = NULL; /* pass-through symbols, symbols with duplicated ports */
  int *symtable = NULL;

  if(what == 0 ) { /* initialize */
    pt_symbol = my_calloc(272, xctx->symbols, sizeof(int));
    symtable = my_calloc(1581,  xctx->symbols, sizeof(int));
    for(i = 0; i < instances; i++) {
      k = inst[i].ptr;
      if( k < 0 || symtable[k] ) continue;
      symtable[k] =1;
      int_hash_init(&table, 37);
      for(j = 0; j < xctx->sym[k].rects[PINLAYER]; j++) {
        const char *pin_name = get_tok_value(xctx->sym[k].rect[PINLAYER][j].prop_ptr, "name", 0);
        if(int_hash_lookup(&table, pin_name, j, XINSERT_NOREPLACE)) {
          dbg(1, "   pass thru symbol found\n");
          pt_symbol[k] = 1;
        }
      }
      int_hash_free(&table);
      if(pt_symbol[k]) dbg(1, "duplicated pins: %s\n", xctx->sym[i].name);
    }
    my_free(831, &symtable);
  } else if(what ==1) { /* query */
    k = inst[ninst].ptr;
    if(k >=0 && pt_symbol[k]) return 1;
    return 0;
  } else if(what ==2) { /* cleanup */
    my_free(832, &pt_symbol);
  }
  return -1;
}

/* 
 * Given an instance pin (inst n, pin p) propagate electrical information through 
 * other pins with identical "name" attribute (pass-through symbols)
 */
static void instcheck(int n, int p)
{
  xInstance * const inst = xctx->inst;
  int j, sqx, sqy;
  double x0, y0;

  /* should process only symbols with pass-through pins */
  if(find_pass_through_symbols(1, n)) {
    int k = inst[n].ptr;
    int rects = xctx->sym[k].rects[PINLAYER];
    char *pin_name = NULL;
    my_strdup(833, &pin_name, get_tok_value(xctx->sym[k].rect[PINLAYER][p].prop_ptr, "name", 0));
    if(p >= rects) return;
    for(j = 0; j < rects; j++) {
      const char *other_pin;
      if(j == p) continue;
      other_pin = get_tok_value(xctx->sym[k].rect[PINLAYER][j].prop_ptr, "name", 0);
      if(!strcmp(other_pin, pin_name)) {
        dbg(1, "instcheck: inst %s pin %s(%d) <--> pin %s(%d)\n", inst[n].instname, pin_name, p, other_pin, j);
        dbg(1, "instcheck: node: %s\n", inst[n].node[p]);
        if(!inst[n].node[j]) {
          set_inst_node(n, j, inst[n].node[p]);
          get_inst_pin_coord(n, j, &x0, &y0);
          get_square(x0, y0, &sqx, &sqy);
          name_attached_nets(x0, y0, sqx, sqy, inst[n].node[j]);
          name_attached_inst(n, x0, y0, sqx, sqy, inst[n].node[j]);
        } else {
          if(for_netlist>0) signal_short("Pass_through symbol", inst[n].node[p], inst[n].node[j]);
        }
      }
    }
    my_free(834, &pin_name);
  }
}

/* starting from labels, ipins, opins, iopins propagate electrical
 * nodes to attached nets and instances
 */
static void name_nodes_of_pins_labels_and_propagate()
{
  int i, sqx, sqy;
  double x0, y0;
  int port;
  char *dir=NULL;
  char *type=NULL;
  char *sig_type=NULL;
  char *verilog_type=NULL;
  char *value=NULL;
  char *class=NULL;
  char *global_node=NULL;
  int print_erc;
  xInstance * const inst = xctx->inst;
  int const instances = xctx->instances;
  static int startlevel = 0; /* safe to keep even with multiple schematic windows, netlist is not interruptable */

  if(xctx->netlist_count == 0 ) startlevel = xctx->currsch;
  dbg(2, "prepare_netlist_structs(): naming pins from attrs\n");
  /* print_erc is 1 the first time prepare_netlist_structs() is called on top level while
   * doing the netlist, when netlist of sub blocks is completed and toplevel is reloaded
   * a second prepare_netlist_structs() is called to name unnamed nets, in this second call
   * print_erc must be set to 0 to avoid double erc printing
   */
  print_erc =  (xctx->netlist_count == 0 || startlevel < xctx->currsch) && for_netlist;
  for (i=0;i<instances;i++) {
    /* name ipin opin label node fields from prop_ptr attributes */
    if(inst[i].ptr<0) continue;

    my_strdup(248, &type,(inst[i].ptr+ xctx->sym)->type);
    if(print_erc && (!inst[i].instname || !inst[i].instname[0]) &&
      !get_tok_value((inst[i].ptr+ xctx->sym)->templ, "name", 0)[0]
        ) {
      char str[2048];
      if(  type &&  /* list of devices that do not have a name= in template attribute */
           strcmp(type, "package") &&  
           strcmp(type, "port_attributes") &&
           strcmp(type, "architecture") &&
           strcmp(type, "arch_declarations") &&
           strcmp(type, "attributes") &&
           strcmp(type, "netlist_options") &&
           strcmp(type, "use")) {
        my_snprintf(str, S(str), "instance: %d (%s): no name attribute set", i, inst[i].name);
        statusmsg(str,2);
        inst[i].color = -PINLAYER;
        xctx->hilight_nets=1;
      }
    }
    if(print_erc && (!type || !type[0]) ) {
      char str[2048];
      my_snprintf(str, S(str), "Symbol: %s: no type attribute set", inst[i].name);
      statusmsg(str,2);
      inst[i].color = -PINLAYER;
      xctx->hilight_nets=1;
    }
    if(type && inst[i].node && IS_LABEL_OR_PIN(type) ) { /* instance must have a pin! */
      if(for_netlist>0) {
        /* 20150918 skip labels / pins if ignore property specified on instance */
        if( xctx->netlist_type == CAD_VERILOG_NETLIST &&
          strcmp(get_tok_value(inst[i].prop_ptr,"verilog_ignore",0),"true")==0 ) continue;
        if( xctx->netlist_type == CAD_SPICE_NETLIST &&
          strcmp(get_tok_value(inst[i].prop_ptr,"spice_ignore",0),"true")==0 ) continue;
        if( xctx->netlist_type == CAD_VHDL_NETLIST &&
          strcmp(get_tok_value(inst[i].prop_ptr,"vhdl_ignore",0),"true")==0 ) continue;
        if( xctx->netlist_type == CAD_TEDAX_NETLIST &&
          strcmp(get_tok_value(inst[i].prop_ptr,"tedax_ignore",0),"true")==0 ) continue;
      }
      port=0;
      my_strdup2(249, &dir, "");
      if(strcmp(type,"label")) {  /* instance is a port (not a label) */
        port=1;
        /* 20071204 only define a dir property if instance is not a label */
        if(for_netlist)
          my_strdup2(250, &dir, get_tok_value( (inst[i].ptr+ xctx->sym)->rect[PINLAYER][0].prop_ptr, "dir",0));
      }
      else {
        /* handle global nodes (global=1 set as symbol property) 28032003 */
        my_strdup(251, &global_node,get_tok_value((inst[i].ptr+ xctx->sym)->prop_ptr,"global",0));
        /*20071204 if instance is a label dont define a dir property for more precise erc checking */
      }
      /* obtain ipin/opin/label signal type (default: std_logic) */
      if(for_netlist) {
        my_strdup(258, &sig_type,get_tok_value(inst[i].prop_ptr,"sig_type",0));
        my_strdup(259, &verilog_type,get_tok_value(inst[i].prop_ptr,"verilog_type",0));
        my_strdup(260, &value,get_tok_value(inst[i].prop_ptr,"value",0));
        my_strdup(261, &class,get_tok_value(inst[i].prop_ptr,"class",0));
      }
      my_strdup(262, &inst[i].node[0], inst[i].lab);
      if(!(inst[i].node[0])) {
        my_strdup(65, &inst[i].node[0], get_tok_value((inst[i].ptr+ xctx->sym)->templ, "lab",0));
        dbg(1, "prepare_netlist_structs(): no lab attr on instance, pick from symbol: %s\n", inst[i].node[0]);
      }
      /* handle global nodes (global=1 set as symbol property) 28032003 */
      if(!strcmp(type,"label") && global_node && !strcmp(global_node, "true")) {
        dbg(1, "prepare_netlist_structs(): global node: %s\n",inst[i].node[0]);
        record_global_node(1,NULL, inst[i].node[0]);
      }

      /* do not count multiple labels/pins with same name */
      bus_node_hash_lookup(inst[i].node[0],    /* insert node in hash table */
        dir, XINSERT, port, sig_type, verilog_type, value, class);

      get_inst_pin_coord(i, 0, &x0, &y0);
      get_square(x0, y0, &sqx, &sqy);
      /* name nets that touch ioin opin alias instances */
      name_attached_nets(x0, y0, sqx, sqy, inst[i].node[0]);
      /* name instances that touch ioin opin alias instances */
      name_attached_inst(i, x0, y0, sqx, sqy, inst[i].node[0]);
    } /* if(type && ... */
  } /* for(i=0;i<instances... */
  my_free(835, &dir);
  my_free(836, &type);
  my_free(841, &global_node);
  if(for_netlist) {
    my_free(837, &sig_type);
    my_free(838, &verilog_type);
    my_free(839, &value);
    my_free(840, &class);
  }
}

static void set_unnamed_net(int i)
{
  char tmp_str[30];
  my_snprintf(tmp_str, S(tmp_str), "#net%d", get_unnamed_node(1,0,0));
  my_strdup(265, &xctx->wire[i].node, tmp_str);
  my_strdup(266, &xctx->wire[i].prop_ptr, subst_token(xctx->wire[i].prop_ptr, "lab", tmp_str));
  /* insert unnamed wire name in hash table */
  bus_node_hash_lookup(tmp_str, "", XINSERT, 0,"","","","");
  wirecheck(i);
}

static void name_unlabeled_nets()
{
  int i;

  /* name nets that do not touch ipin opin alias instances */
  dbg(2, "prepare_netlist_structs(): naming nets that dont touch labels\n");
  for (i = 0; i < xctx->wires; i++)
  {
    if(xctx->wire[i].node == NULL)
    {
      set_unnamed_net(i);
    }
  }
}

static void set_unnamed_inst(int i, int j)
{
  char tmp_str[30];
  xInstance * const inst = xctx->inst;
  int sqx, sqy;
  double x0, y0;
  my_snprintf(tmp_str, S(tmp_str), "#net%d", get_unnamed_node(1,0,0));
  dbg(1, "set_unnamed_inst(): inst %s pin %d, net %s\n", inst[i].instname, j, tmp_str);
  set_inst_node(i, j, tmp_str);
  get_inst_pin_coord(i, j, &x0, &y0);
  get_square(x0, y0, &sqx, &sqy);
  name_attached_inst(i, x0, y0, sqx, sqy, inst[i].node[j]);
}

static void name_unlabeled_instances()
{ 
  int i, j;
  xInstance * const inst = xctx->inst;
  int const instances = xctx->instances;
  int rects;
    
  /* name nets that do not touch ipin opin alias instances */
  dbg(2, "prepare_netlist_structs(): naming nets that dont touch labels\n");
  for (i = 0; i < instances; i++)
  {
    rects=(inst[i].ptr+ xctx->sym)->rects[PINLAYER];
    for(j = 0; j < rects; j++) {
      if(inst[i].node[j] == NULL)
      {
        set_unnamed_inst(i, j);
      }
    }
  }
} 


static void reset_node_data_and_rehash()
{
  int i,j, rects;
  xInstance * const inst = xctx->inst;
  int const instances = xctx->instances;

  /* reset wire & inst node labels */
  dbg(2, "prepare_netlist_structs(): rehashing wires and instance pins in spatial hash table\n");
  hash_wires();
  for (i=0;i<instances;i++)
  {
    if(inst[i].ptr<0) continue;
    rects=(inst[i].ptr+ xctx->sym)->rects[PINLAYER] +
          (inst[i].ptr+ xctx->sym)->rects[GENERICLAYER];
    if(rects > 0)
    {
      inst[i].node = my_malloc(247, sizeof(char *) * rects);
      for (j=0;j<rects;j++)
      {
        inst[i].node[j]=NULL;
        hash_inst_pin(XINSERT, i, j);
      }
    }
  }
}

void prepare_netlist_structs(int for_netl)
{
  char nn[PATH_MAX+30];
 
  for_netlist = for_netl;
  if(for_netlist>0 && xctx->prep_net_structs) return;
  else if(!for_netlist && xctx->prep_hi_structs) return;
  /* delete instance pins spatial hash, wires spatial hash, node_hash, wires and inst nodes.*/
  if(for_netlist) {
    my_snprintf(nn, S(nn), "-----------%s", xctx->sch[xctx->currsch]);
    statusmsg(nn,2);
  }
  dbg(1, "prepare_netlist_structs(): extraction: %s\n", xctx->sch[xctx->currsch]);
  delete_netlist_structs();
  free_simdata(); /* invalidate simulation cache */
  reset_node_data_and_rehash();
  get_unnamed_node(0,0,0); /*initializes node multiplicity data struct */
  find_pass_through_symbols(0, 0); /* initialize data struct to quickly find pass-through syms */
  name_nodes_of_pins_labels_and_propagate();
  name_unlabeled_nets();
  name_unlabeled_instances();
  name_generics();
  /* name_non_label_inst_pins(); */

  find_pass_through_symbols(2, 0); /* cleanup data */
  rebuild_selected_array();
  if(for_netlist>0) {
    xctx->prep_net_structs=1;
    xctx->prep_hi_structs=1;
  } else xctx->prep_hi_structs=1;
  dbg(1, "prepare_netlist_structs(): returning\n");
  /* avoid below call: it in turn calls prepare_netlist_structs(), too many side effects */
  /* propagate_hilights(1, 0, XINSERT_NOREPLACE);*/
}

void delete_inst_node(int i)
{
   int j, rects;
   if( xctx->inst[i].ptr == -1 || !xctx->inst[i].node) return;
   rects = (xctx->inst[i].ptr+ xctx->sym)->rects[PINLAYER] +
           (xctx->inst[i].ptr+ xctx->sym)->rects[GENERICLAYER];
   if( rects > 0 )
   {
     for(j=0;j< rects ;j++)
       my_free(849, &xctx->inst[i].node[j]);
     my_free(850, &xctx->inst[i].node );
   }
}

void delete_netlist_structs(void)
{
 int i;
  /* erase node data structures */
   dbg(1, "delete_netlist_structs(): begin erasing\n");
  for(i=0;i<xctx->instances;i++)
  {
   delete_inst_node(i);
  }
  for(i=0;i<xctx->wires;i++)
  {
    my_free(851, &xctx->wire[i].node);
  }
  /* erase inst and wire topological hash tables */
  del_inst_pin_table();
  node_hash_free();
  dbg(1, "delete_netlist_structs(): end erasing\n");
  xctx->prep_net_structs=0;
  xctx->prep_hi_structs=0;
}

int warning_overlapped_symbols(int sel)
{
  int i;
  Int_hashtable table = {NULL, 0};
  Int_hashentry *found;
  char str[2048];
  char s[512];

  int_hash_init(&table, HASHSIZE);
  for(i = 0; i < xctx->instances; i++) {
    dbg(1, "instance:%s: %s\n", xctx->inst[i].instname, xctx->inst[i].name);
    my_snprintf(s, S(s), "%g %g %g %g",
       xctx->inst[i].xx1, xctx->inst[i].yy1, xctx->inst[i].xx2, xctx->inst[i].yy2);

    dbg(1, "  bbox: %g %g %g %g\n", xctx->inst[i].xx1, xctx->inst[i].yy1, xctx->inst[i].xx2, xctx->inst[i].yy2);
    dbg(1, "  s=%s\n", s);
    found =  int_hash_lookup(&table, s, i, XINSERT_NOREPLACE);
    if(found) {
      if(sel == 0) {
        xctx->inst[i].color = -PINLAYER;
        xctx->hilight_nets=1;
      } else {
        xctx->inst[i].sel = SELECTED;
        xctx->need_reb_sel_arr = 1;
      }
      my_snprintf(str, S(str), "Warning: overlapped instance found: %s(%s) -> %s\n",
            xctx->inst[i].instname, xctx->inst[i].name, xctx->inst[found->value].instname);
      statusmsg(str,2);
      tcleval("show_infotext"); /* critical error: force ERC window showing */
    }
  }
  int_hash_free(&table);
  if(sel && xctx->need_reb_sel_arr) rebuild_selected_array();
  return 0;
}

int sym_vs_sch_pins()
{
  char **lab_array =NULL;
  int lab_array_size = 0;
  int i, j, k, symbol, n_syms, rects, pin_cnt=0, pin_match, mult;
  struct stat buf;
  char name[PATH_MAX];
  char *type = NULL;
  char *tmp = NULL;
  char *lab=NULL;
  char *pin_name=NULL;
  char *pin_dir=NULL;
  double tmpd;
  FILE *fd;
  int tmpi;
  short tmps;
  int endfile;
  char tag[1];
  char filename[PATH_MAX];
  n_syms = xctx->symbols;
  for(i=0;i<n_syms;i++)
  {
    if( xctx->sym[i].type && !strcmp(xctx->sym[i].type,"subcircuit")) {
      rects = xctx->sym[i].rects[PINLAYER];

      get_sch_from_sym(filename, xctx->sym + i);
      if(!stat(filename, &buf)) {
        fd = fopen(filename, "r");
        pin_cnt = 0;
        endfile = 0;
        xctx->file_version[0] = '\0';
        while(!endfile) {
          if(fscanf(fd," %c",tag)==EOF) break;
          switch(tag[0]) {
            case 'v':
             load_ascii_string(&xctx->version_string, fd);
             my_snprintf(xctx->file_version, S(xctx->file_version), "%s", 
                         get_tok_value(xctx->version_string, "file_version", 0));
            break;

            case 'E':
            case 'S':
            case 'V':
            case 'K':
            case 'G':
              load_ascii_string(&tmp, fd);
              break;
            case '#':
              read_line(fd, 1);
              break;
            case 'F': /* extension for future symbol floater labels */
              read_line(fd, 1);
              break;
            case 'L':
            case 'B':
              if(fscanf(fd, "%d",&tmpi)< 1) {
                 fprintf(errfp,"sym_vs_sch_pins(): WARNING:  missing fields for LINE/BOX object, ignoring\n");
                 read_line(fd, 0);
                 break;
              }
            case 'N':
              if(fscanf(fd, "%lf %lf %lf %lf ",&tmpd, &tmpd, &tmpd, &tmpd) < 4) {
                 fprintf(errfp,"sym_vs_sch_pins(): WARNING:  missing fields for LINE/BOX object, ignoring\n");
                 read_line(fd, 0);
                 break;
               }
               load_ascii_string(&tmp, fd);
              break;
            case 'P':
              if(fscanf(fd, "%d %d",&tmpi, &tmpi)<2) {
                fprintf(errfp,"sym_vs_sch_pins(): WARNING: missing fields for POLYGON object, ignoring.\n");
                read_line(fd, 0);
                break;
              }
              for(j=0;j<tmpi;j++) {
                if(fscanf(fd, "%lf %lf ",&tmpd, &tmpd)<2) {
                  fprintf(errfp,"sym_vs_sch_pins(): WARNING: missing fields for POLYGON points, ignoring.\n");
                  read_line(fd, 0);
                }
              }
              load_ascii_string( &tmp, fd);
              break;
            case 'A':
              if(fscanf(fd, "%d",&tmpi)< 1) {
                 fprintf(errfp,"sym_vs_sch_pins(): WARNING:  missing fields for ARC object, ignoring\n");
                 read_line(fd, 0);
                 break;
              }
              if(fscanf(fd, "%lf %lf %lf %lf %lf ",&tmpd, &tmpd, &tmpd, &tmpd, &tmpd) < 5) {
                fprintf(errfp,"sym_vs_sch_pins(): WARNING:  missing fields for ARC object, ignoring\n");
                read_line(fd, 0);
                break;
              }
              load_ascii_string(&tmp, fd);
              break;
            case 'T':
              load_ascii_string(&tmp,fd);
              if(fscanf(fd, "%lf %lf %hd %hd %lf %lf ", &tmpd, &tmpd, &tmps, &tmps, &tmpd, &tmpd) < 6 ) {
                fprintf(errfp,"sym_vs_sch_pins(): WARNING:  missing fields for TEXT object, ignoring\n");
                read_line(fd, 0);
                break;
              }
              load_ascii_string(&tmp,fd);
              break;
            case 'C':
              load_ascii_string(&tmp, fd);
              my_strncpy(name, tmp, S(name));

              if(!strcmp(xctx->file_version,"1.0") ) {
                dbg(1, "sym_vs_sch_pins(): add_ext(name,\".sym\") = %s\n", add_ext(name, ".sym") );
                my_strncpy(name, add_ext(name, ".sym"), S(name));
              }

              if(fscanf(fd, "%lf %lf %hd %hd", &tmpd, &tmpd, &tmps, &tmps) < 4) {
                fprintf(errfp,"sym_vs_sch_pins() WARNING: missing fields for INST object, filename=%s\n",
                  filename);
                read_line(fd, 0);
                break;
              }
              load_ascii_string(&tmp,fd);
              symbol = match_symbol(name);
              my_strdup(276, &type, xctx->sym[symbol].type);
              if(type && IS_PIN(type)) {
                my_strdup(292, &lab, expandlabel(get_tok_value(tmp, "lab", 0), &mult));
                if(pin_cnt >= lab_array_size) {
                  lab_array_size += CADCHUNKALLOC;
                  my_realloc(154, &lab_array, lab_array_size * sizeof(char *));
                }
                lab_array[pin_cnt] = NULL;
                my_strdup(155, &(lab_array[pin_cnt]), lab);
                pin_cnt++;
                pin_match = 0;
                for(j=0; j < rects; j++) {
                  my_strdup(293, &pin_name, 
                    expandlabel(get_tok_value(xctx->sym[i].rect[PINLAYER][j].prop_ptr, "name", 0), &mult));
                  my_strdup(294, &pin_dir, get_tok_value(xctx->sym[i].rect[PINLAYER][j].prop_ptr, "dir", 0));
                  if( pin_name && !strcmp(pin_name, lab)) {
                    if(!(
                          ( !strcmp(type, "ipin") && !strcmp(pin_dir, "in") ) ||
                          ( !strcmp(type, "opin") && !strcmp(pin_dir, "out") ) ||
                          ( !strcmp(type, "iopin") && !strcmp(pin_dir, "inout") )
                        )
                      ) {
                      char str[2048];
                      my_snprintf(str, S(str), "Symbol %s: Unmatched subcircuit schematic pin direction: %s",
                                  xctx->sym[i].name, lab);
                      statusmsg(str,2);
                      my_snprintf(str, S(str), "    %s <--> %s", type, pin_dir);
                      statusmsg(str,2);
                      tcleval("show_infotext"); /* critical error: force ERC window showing */
                      for(j = 0; j < xctx->instances; j++) {
                        if(!xctx->x_strcmp(xctx->inst[j].name, xctx->sym[i].name)) {
                          xctx->inst[i].color = -PINLAYER;
                          xctx->hilight_nets=1;
                        }
                      }
                    }
                    pin_match++;
                    break;
                  }
                }
                if(!pin_match) {
                  char str[2048];
                  /* fprintf(errfp, "  unmatched sch / sym pin: %s\n", lab); */
                  my_snprintf(str, S(str), "Symbol %s: schematic pin: %s not in symbol", xctx->sym[i].name, lab);
                  statusmsg(str,2);
                  tcleval("show_infotext"); /* critical error: force ERC window showing */
                  for(j = 0; j < xctx->instances; j++) {
                    if(!xctx->x_strcmp(xctx->inst[j].name, xctx->sym[i].name)) {
                      xctx->inst[i].color = -PINLAYER;
                      xctx->hilight_nets=1;
                    }
                  }
                }
              }
              break;
            case '[':
              load_sym_def(name, fd);
              break;
            case ']':
              read_line(fd, 0);
              endfile=1;
              break;
            default:
              if( tag[0] == '{' ) ungetc(tag[0], fd);
              read_record(tag[0], fd, 0);
              break;
          }
          read_line(fd, 0); /* discard any remaining characters till (but not including) newline */
          if(!xctx->file_version[0]) {
            my_snprintf(xctx->file_version, S(xctx->file_version), "1.0");
            dbg(1, "sym_vs_sch_pins(): no file_version, assuming file_version=%s\n", xctx->file_version);
          }
        } /* while(!endfile) */
        fclose(fd);
        if(pin_cnt != rects) {
          char str[2048];
          my_snprintf(str, S(str), "Symbol %s has %d pins, its schematic has %d pins",
                      xctx->sym[i].name, rects, pin_cnt);
          statusmsg(str,2);
          tcleval("show_infotext"); /* critical error: force ERC window showing */
          for(j = 0; j < xctx->instances; j++) {
            if(!xctx->x_strcmp(xctx->inst[j].name, xctx->sym[i].name)) {
              xctx->inst[i].color = -PINLAYER;
              xctx->hilight_nets=1;
            }
          }
        }
        for(j=0; j < rects; j++) {
          my_strdup(295, &pin_name,
             expandlabel(get_tok_value(xctx->sym[i].rect[PINLAYER][j].prop_ptr, "name", 0), &mult));
          pin_match = 0;
          for(k=0; k<pin_cnt; k++) {
            if(pin_name && !strcmp(lab_array[k], pin_name)) {
              pin_match++;
              break;
            }
          }
          if(!pin_match) {
            char str[2048];
            /* fprintf(errfp, "  unmatched sch / sym pin: %s\n", lab); */
            my_snprintf(str, S(str), "Symbol %s: symbol pin: %s not in schematic",
                        xctx->sym[i].name, pin_name ? pin_name : "<NULL>");
            statusmsg(str,2);
            tcleval("show_infotext"); /* critical error: force ERC window showing */
            for(k = 0; k < xctx->instances; k++) {
              if(!xctx->x_strcmp(xctx->inst[k].name, xctx->sym[i].name)) {
                xctx->inst[i].color = -PINLAYER;
                xctx->hilight_nets=1;
              }
            }
          }
        }
      }
      if(lab_array_size) {
        for(k=0;k<pin_cnt;k++) {
          my_free(842, &(lab_array[k]));
        }
        my_free(843, &lab_array);
        lab_array_size = 0;
        pin_cnt=0;
      }
    } /* if( ... "subcircuit"... ) */
    my_free(844, &type);
    my_free(845, &tmp);
    my_free(846, &lab);
    my_free(847, &pin_name);
    my_free(848, &pin_dir);
  } /* for(i=0;i<n_syms;i++) */

  while(xctx->symbols > n_syms) remove_symbol(xctx->symbols - 1);
  return 0;
}
