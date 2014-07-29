


/*
 *
 * IF-2.0 Intermediate Representation.
 * 
 * Copyright (C) Verimag Grenoble.
 *
 * Marius Bozga
 *
 */


#include <iostream>
#include <strstream>
#include "simulator.h"
#include "propertyInitPid2.h"
#include "filter.h"








inline void if_RTDS_charstring_copy
    (if_RTDS_charstring_type& x, const if_RTDS_charstring_type y) {
  if_RTDS_charstring_reset(x);
  for(int i=0;i<y.length;i++)
    if_RTDS_character_copy(x.elem[i],y.elem[i]);
  x.length=y.length;
}
inline int if_RTDS_charstring_compare
    (const if_RTDS_charstring_type x, const if_RTDS_charstring_type y) {
  int c = x.length-y.length;
  for(int i=0;i<x.length && !c;i++)
    c = if_RTDS_character_compare(x.elem[i],y.elem[i]);
  return c;
}
inline void if_RTDS_charstring_print
    (const if_RTDS_charstring_type x, FILE* f) {
  fprintf(f,"{");
  for(int i=0;i<x.length;i++) {
    if_RTDS_character_print(x.elem[i],f);
    fprintf(f,",");
  }
  fprintf(f,"}");
}
inline void if_RTDS_charstring_print_xml
    (const if_RTDS_charstring_type x, std::ostream& b) {
  b << "<string>\n";
  for(int i=0;i<x.length;i++) {
    if_RTDS_character_print_xml(x.elem[i],b);
  }
  b << "</string>\n";
}
inline void if_RTDS_charstring_reset
    (if_RTDS_charstring_type& x) {
  x.length=0;	
  for(int i=0;i<128;i++)
    if_RTDS_character_reset(x.elem[i]);
}

inline int if_RTDS_charstring_length
    (const if_RTDS_charstring_type x) {
  return x.length;
}
if_RTDS_charstring_type if_RTDS_charstring_make
    () {
  if_RTDS_charstring_type z;
  if_RTDS_charstring_reset(z);
  return z;
}
if_RTDS_charstring_type if_RTDS_charstring_make
    (const if_RTDS_character_type e) {
  if_RTDS_charstring_type z;
  if_RTDS_charstring_reset(z);
  if (0<128) {
    if_RTDS_character_copy(z.elem[0],e);
    z.length=1;
  }
  return z;
}
if_RTDS_charstring_type if_RTDS_charstring_concat
    (const if_RTDS_charstring_type x, const if_RTDS_charstring_type y) {
  if_RTDS_charstring_type z;
  if_RTDS_charstring_reset(z);
  int i;

  for(i=0;i<x.length && z.length<128;i++,z.length++) 
    if_RTDS_character_copy(z.elem[z.length],x.elem[i]);
  for(i=0;i<y.length && z.length<128;i++,z.length++)
    if_RTDS_character_copy(z.elem[z.length],y.elem[i]);
  return z;
}
if_RTDS_charstring_type if_RTDS_charstring_substring
    (const if_RTDS_charstring_type x, const int k, const int l) {
  if_RTDS_charstring_type z;
  if_RTDS_charstring_reset(z);
  for(int i=k;i<=l && 
              i<x.length && z.length<128; i++,z.length++)
    if_RTDS_character_copy(z.elem[z.length], x.elem[i]);
  return z;
}
if_RTDS_charstring_type if_RTDS_charstring_remove
    (const if_RTDS_charstring_type x, const int k) {
  if_RTDS_charstring_type z;
  if_RTDS_charstring_reset(z);
  if (0<=k && k<x.length) 
    for(int i=0;i<x.length;i++,z.length++) {
      if_RTDS_character_copy(z.elem[z.length],x.elem[i]);
      if (i==k) z.length--;
    }
  else
    if_RTDS_charstring_copy(z,x);
  return z;
}
if_RTDS_charstring_type if_RTDS_charstring_insert
    (const if_RTDS_charstring_type x, const int k, const if_RTDS_character_type e) {
  if_RTDS_charstring_type z;
  if_RTDS_charstring_reset(z);
  if (0<=k && k<=x.length && x.length<128) {
    int i;
    for(i=0;i<k;i++,z.length++) 
      if_RTDS_character_copy(z.elem[z.length],x.elem[i]);
    if_RTDS_character_copy(z.elem[z.length++],e);
    for(i=k;i<x.length;i++,z.length++) 
      if_RTDS_character_copy(z.elem[z.length],x.elem[i]);
  }
  else 
    if_RTDS_charstring_copy(z,x);
  return z;
}
int if_RTDS_charstring_index
    (const if_RTDS_charstring_type x, const if_RTDS_character_type e) {
  int idx = -1;
  for(int i=0;i<x.length && idx<0;i++)
    if (if_RTDS_character_compare(x.elem[i],e)==0)
      idx = i;
  return idx;
}


inline void if_InfoZone_copy
    (if_InfoZone_type& x, const if_InfoZone_type y) {
  if_i_spots_copy(x.totalSpots,y.totalSpots);
  if_i_spots_copy(x.freeSpots,y.freeSpots);
  if_pid_copy(x.ID,y.ID);
}
inline int if_InfoZone_compare
    (const if_InfoZone_type x, const if_InfoZone_type y) {
  int c = 0;
  if (c == 0) c = if_i_spots_compare(x.totalSpots,y.totalSpots);
  if (c == 0) c = if_i_spots_compare(x.freeSpots,y.freeSpots);
  if (c == 0) c = if_pid_compare(x.ID,y.ID);
  return c;
}
inline void if_InfoZone_print
    (const if_InfoZone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"totalSpots="); if_i_spots_print(x.totalSpots,f); fprintf(f,",");
  fprintf(f,"freeSpots="); if_i_spots_print(x.freeSpots,f); fprintf(f,",");
  fprintf(f,"ID="); if_pid_print(x.ID,f);
  fprintf(f,"}");
}
inline void if_InfoZone_print_xml
    (const if_InfoZone_type x, std::ostream& b) { 
  b << "<InfoZone>\n";
  b << "<totalSpots>"; if_i_spots_print_xml(x.totalSpots,b); b << "</totalSpots>";
  b << "<freeSpots>"; if_i_spots_print_xml(x.freeSpots,b); b << "</freeSpots>";
  b << "<ID>"; if_pid_print_xml(x.ID,b); b << "</ID>"; 
  b << "</InfoZone>\n";
}
inline void if_InfoZone_reset
    (if_InfoZone_type& x) {
  if_i_spots_reset(x.totalSpots);
  if_i_spots_reset(x.freeSpots);
  if_pid_reset(x.ID);
}

inline if_InfoZone_type if_InfoZone_make
    (if_i_spots_type totalSpots,if_i_spots_type freeSpots,if_pid_type ID) {
  if_InfoZone_type m_par;
  if_i_spots_copy(m_par.totalSpots,totalSpots);
  if_i_spots_copy(m_par.freeSpots,freeSpots);
  if_pid_copy(m_par.ID,ID);
  return m_par;
}

inline void if_t_sEntered_Car_copy
    (if_t_sEntered_Car_type& x, const if_t_sEntered_Car_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_t_sEntered_Car_compare
    (const if_t_sEntered_Car_type x, const if_t_sEntered_Car_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sEntered_Car_print
    (const if_t_sEntered_Car_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sEntered_Car_print_xml
    (const if_t_sEntered_Car_type x, std::ostream& b) { 
  b << "<t_sEntered_Car>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sEntered_Car>\n";
}
inline void if_t_sEntered_Car_reset
    (if_t_sEntered_Car_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_t_sEntered_Car_type if_t_sEntered_Car_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_t_sEntered_Car_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_sOut_Car_copy
    (if_t_sOut_Car_type& x, const if_t_sOut_Car_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_t_sOut_Car_compare
    (const if_t_sOut_Car_type x, const if_t_sOut_Car_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sOut_Car_print
    (const if_t_sOut_Car_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sOut_Car_print_xml
    (const if_t_sOut_Car_type x, std::ostream& b) { 
  b << "<t_sOut_Car>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sOut_Car>\n";
}
inline void if_t_sOut_Car_reset
    (if_t_sOut_Car_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_t_sOut_Car_type if_t_sOut_Car_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_t_sOut_Car_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_sOkInit_copy
    (if_t_sOkInit_type& x, const if_t_sOkInit_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_t_sOkInit_compare
    (const if_t_sOkInit_type x, const if_t_sOkInit_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sOkInit_print
    (const if_t_sOkInit_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sOkInit_print_xml
    (const if_t_sOkInit_type x, std::ostream& b) { 
  b << "<t_sOkInit>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sOkInit>\n";
}
inline void if_t_sOkInit_reset
    (if_t_sOkInit_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_t_sOkInit_type if_t_sOkInit_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_t_sOkInit_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_sInfoZone_copy
    (if_t_sInfoZone_type& x, const if_t_sInfoZone_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_t_sInfoZone_compare
    (const if_t_sInfoZone_type x, const if_t_sInfoZone_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sInfoZone_print
    (const if_t_sInfoZone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sInfoZone_print_xml
    (const if_t_sInfoZone_type x, std::ostream& b) { 
  b << "<t_sInfoZone>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sInfoZone>\n";
}
inline void if_t_sInfoZone_reset
    (if_t_sInfoZone_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_t_sInfoZone_type if_t_sInfoZone_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_t_sInfoZone_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_sInitFreeSpot_copy
    (if_t_sInitFreeSpot_type& x, const if_t_sInitFreeSpot_type y) {
  if_pid_copy(x.p1,y.p1);
  if_i_spots_copy(x.p2,y.p2);
}
inline int if_t_sInitFreeSpot_compare
    (const if_t_sInitFreeSpot_type x, const if_t_sInitFreeSpot_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_i_spots_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sInitFreeSpot_print
    (const if_t_sInitFreeSpot_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_i_spots_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sInitFreeSpot_print_xml
    (const if_t_sInitFreeSpot_type x, std::ostream& b) { 
  b << "<t_sInitFreeSpot>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_i_spots_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sInitFreeSpot>\n";
}
inline void if_t_sInitFreeSpot_reset
    (if_t_sInitFreeSpot_type& x) {
  if_pid_reset(x.p1);
  if_i_spots_reset(x.p2);
}

inline if_t_sInitFreeSpot_type if_t_sInitFreeSpot_make
    (if_pid_type p1,if_i_spots_type p2) {
  if_t_sInitFreeSpot_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_i_spots_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_sInitTotalSpots_copy
    (if_t_sInitTotalSpots_type& x, const if_t_sInitTotalSpots_type y) {
  if_pid_copy(x.p1,y.p1);
  if_i_spots_copy(x.p2,y.p2);
}
inline int if_t_sInitTotalSpots_compare
    (const if_t_sInitTotalSpots_type x, const if_t_sInitTotalSpots_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_i_spots_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sInitTotalSpots_print
    (const if_t_sInitTotalSpots_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_i_spots_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sInitTotalSpots_print_xml
    (const if_t_sInitTotalSpots_type x, std::ostream& b) { 
  b << "<t_sInitTotalSpots>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_i_spots_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sInitTotalSpots>\n";
}
inline void if_t_sInitTotalSpots_reset
    (if_t_sInitTotalSpots_type& x) {
  if_pid_reset(x.p1);
  if_i_spots_reset(x.p2);
}

inline if_t_sInitTotalSpots_type if_t_sInitTotalSpots_make
    (if_pid_type p1,if_i_spots_type p2) {
  if_t_sInitTotalSpots_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_i_spots_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_sReqInfo_copy
    (if_t_sReqInfo_type& x, const if_t_sReqInfo_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sReqInfo_compare
    (const if_t_sReqInfo_type x, const if_t_sReqInfo_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sReqInfo_print
    (const if_t_sReqInfo_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sReqInfo_print_xml
    (const if_t_sReqInfo_type x, std::ostream& b) { 
  b << "<t_sReqInfo>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sReqInfo>\n";
}
inline void if_t_sReqInfo_reset
    (if_t_sReqInfo_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sReqInfo_type if_t_sReqInfo_make
    (if_pid_type p1) {
  if_t_sReqInfo_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sLoopInductive_Zone_copy
    (if_t_sLoopInductive_Zone_type& x, const if_t_sLoopInductive_Zone_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sLoopInductive_Zone_compare
    (const if_t_sLoopInductive_Zone_type x, const if_t_sLoopInductive_Zone_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sLoopInductive_Zone_print
    (const if_t_sLoopInductive_Zone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sLoopInductive_Zone_print_xml
    (const if_t_sLoopInductive_Zone_type x, std::ostream& b) { 
  b << "<t_sLoopInductive_Zone>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sLoopInductive_Zone>\n";
}
inline void if_t_sLoopInductive_Zone_reset
    (if_t_sLoopInductive_Zone_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sLoopInductive_Zone_type if_t_sLoopInductive_Zone_make
    (if_pid_type p1) {
  if_t_sLoopInductive_Zone_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sIR1_Zone_copy
    (if_t_sIR1_Zone_type& x, const if_t_sIR1_Zone_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sIR1_Zone_compare
    (const if_t_sIR1_Zone_type x, const if_t_sIR1_Zone_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sIR1_Zone_print
    (const if_t_sIR1_Zone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sIR1_Zone_print_xml
    (const if_t_sIR1_Zone_type x, std::ostream& b) { 
  b << "<t_sIR1_Zone>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sIR1_Zone>\n";
}
inline void if_t_sIR1_Zone_reset
    (if_t_sIR1_Zone_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sIR1_Zone_type if_t_sIR1_Zone_make
    (if_pid_type p1) {
  if_t_sIR1_Zone_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sIR2_Zone_copy
    (if_t_sIR2_Zone_type& x, const if_t_sIR2_Zone_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sIR2_Zone_compare
    (const if_t_sIR2_Zone_type x, const if_t_sIR2_Zone_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sIR2_Zone_print
    (const if_t_sIR2_Zone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sIR2_Zone_print_xml
    (const if_t_sIR2_Zone_type x, std::ostream& b) { 
  b << "<t_sIR2_Zone>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sIR2_Zone>\n";
}
inline void if_t_sIR2_Zone_reset
    (if_t_sIR2_Zone_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sIR2_Zone_type if_t_sIR2_Zone_make
    (if_pid_type p1) {
  if_t_sIR2_Zone_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sIR3_Zone_copy
    (if_t_sIR3_Zone_type& x, const if_t_sIR3_Zone_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sIR3_Zone_compare
    (const if_t_sIR3_Zone_type x, const if_t_sIR3_Zone_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sIR3_Zone_print
    (const if_t_sIR3_Zone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sIR3_Zone_print_xml
    (const if_t_sIR3_Zone_type x, std::ostream& b) { 
  b << "<t_sIR3_Zone>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sIR3_Zone>\n";
}
inline void if_t_sIR3_Zone_reset
    (if_t_sIR3_Zone_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sIR3_Zone_type if_t_sIR3_Zone_make
    (if_pid_type p1) {
  if_t_sIR3_Zone_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sIR4_Zone_copy
    (if_t_sIR4_Zone_type& x, const if_t_sIR4_Zone_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sIR4_Zone_compare
    (const if_t_sIR4_Zone_type x, const if_t_sIR4_Zone_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sIR4_Zone_print
    (const if_t_sIR4_Zone_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sIR4_Zone_print_xml
    (const if_t_sIR4_Zone_type x, std::ostream& b) { 
  b << "<t_sIR4_Zone>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sIR4_Zone>\n";
}
inline void if_t_sIR4_Zone_reset
    (if_t_sIR4_Zone_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sIR4_Zone_type if_t_sIR4_Zone_make
    (if_pid_type p1) {
  if_t_sIR4_Zone_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sTemp_copy
    (if_t_sTemp_type& x, const if_t_sTemp_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sTemp_compare
    (const if_t_sTemp_type x, const if_t_sTemp_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sTemp_print
    (const if_t_sTemp_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sTemp_print_xml
    (const if_t_sTemp_type x, std::ostream& b) { 
  b << "<t_sTemp>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sTemp>\n";
}
inline void if_t_sTemp_reset
    (if_t_sTemp_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sTemp_type if_t_sTemp_make
    (if_pid_type p1) {
  if_t_sTemp_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sOkInitPid_copy
    (if_t_sOkInitPid_type& x, const if_t_sOkInitPid_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_t_sOkInitPid_compare
    (const if_t_sOkInitPid_type x, const if_t_sOkInitPid_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_t_sOkInitPid_print
    (const if_t_sOkInitPid_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_t_sOkInitPid_print_xml
    (const if_t_sOkInitPid_type x, std::ostream& b) { 
  b << "<t_sOkInitPid>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</t_sOkInitPid>\n";
}
inline void if_t_sOkInitPid_reset
    (if_t_sOkInitPid_type& x) {
  if_pid_reset(x.p1);
}

inline if_t_sOkInitPid_type if_t_sOkInitPid_make
    (if_pid_type p1) {
  if_t_sOkInitPid_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

inline void if_t_sInitPidCtrl_copy
    (if_t_sInitPidCtrl_type& x, const if_t_sInitPidCtrl_type y) {
  if_pid_copy(x.p1,y.p1);
  if_pid_copy(x.p2,y.p2);
}
inline int if_t_sInitPidCtrl_compare
    (const if_t_sInitPidCtrl_type x, const if_t_sInitPidCtrl_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_pid_compare(x.p2,y.p2);
  return c;
}
inline void if_t_sInitPidCtrl_print
    (const if_t_sInitPidCtrl_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_pid_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_t_sInitPidCtrl_print_xml
    (const if_t_sInitPidCtrl_type x, std::ostream& b) { 
  b << "<t_sInitPidCtrl>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_pid_print_xml(x.p2,b); b << "</p2>"; 
  b << "</t_sInitPidCtrl>\n";
}
inline void if_t_sInitPidCtrl_reset
    (if_t_sInitPidCtrl_type& x) {
  if_pid_reset(x.p1);
  if_pid_reset(x.p2);
}

inline if_t_sInitPidCtrl_type if_t_sInitPidCtrl_make
    (if_pid_type p1,if_pid_type p2) {
  if_t_sInitPidCtrl_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_pid_copy(m_par.p2,p2);
  return m_par;
}

inline void if_t_if_signal_copy
    (if_t_if_signal_type& x, const if_t_if_signal_type y) {
  x = y;
}
inline int if_t_if_signal_compare
    (const if_t_if_signal_type x, const if_t_if_signal_type y) {
  int c = x - y;
  if(c || x == NULL) return c;
  return x->compare(y);
}
inline void if_t_if_signal_print
    (const if_t_if_signal_type x, FILE* f) { 
  fprintf(f,"{");
  if(x) x->print(f);
  else fprintf(f,"nil");
  fprintf(f,"}");
}
inline void if_t_if_signal_print_xml
    (const if_t_if_signal_type x, std::ostream& b) { 
  b << "<sigunion>\n";
  if(x) x->printXML(b);
  b << "</sigunion>\n";
}
inline void if_t_if_signal_reset
    (if_t_if_signal_type& x) {
  x = NULL;
}



/*
 * sEntered_Car message implementation 
 *
 */


inline void if_sEntered_Car_par_copy
    (if_sEntered_Car_par_type& x, const if_sEntered_Car_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_sEntered_Car_par_compare
    (const if_sEntered_Car_par_type x, const if_sEntered_Car_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_sEntered_Car_par_print
    (const if_sEntered_Car_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sEntered_Car_par_print_xml
    (const if_sEntered_Car_par_type x, std::ostream& b) { 
  b << "<sEntered_Car_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sEntered_Car_par>\n";
}
inline void if_sEntered_Car_par_reset
    (if_sEntered_Car_par_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_sEntered_Car_par_type if_sEntered_Car_par_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_sEntered_Car_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sEntered_Car_message::NAME = IfMessage::SIGNAME[0] = "sEntered_Car";

if_sEntered_Car_message::if_sEntered_Car_message() 
  : IfMessage(if_sEntered_Car_signal) {
  if_sEntered_Car_par_reset(m_par);
}

if_sEntered_Car_message::if_sEntered_Car_message(if_pid_type p1,if_InfoZone_type p2) 
  : IfMessage(if_sEntered_Car_signal) {
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
}

if_sEntered_Car_message::if_sEntered_Car_message(const if_sEntered_Car_message& message) 
  : IfMessage(message) {
  if_sEntered_Car_par_copy(m_par,message.m_par);
}

int if_sEntered_Car_message::compare(const IfMessage* X) const {
  if_sEntered_Car_message* x = (if_sEntered_Car_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sEntered_Car_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sEntered_Car_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sEntered_Car_message::copy() const {
  return new if_sEntered_Car_message(*this);
}

void if_sEntered_Car_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sEntered_Car_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sEntered_Car_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sEntered_Car_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sOut_Car message implementation 
 *
 */


inline void if_sOut_Car_par_copy
    (if_sOut_Car_par_type& x, const if_sOut_Car_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_sOut_Car_par_compare
    (const if_sOut_Car_par_type x, const if_sOut_Car_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_sOut_Car_par_print
    (const if_sOut_Car_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sOut_Car_par_print_xml
    (const if_sOut_Car_par_type x, std::ostream& b) { 
  b << "<sOut_Car_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sOut_Car_par>\n";
}
inline void if_sOut_Car_par_reset
    (if_sOut_Car_par_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_sOut_Car_par_type if_sOut_Car_par_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_sOut_Car_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sOut_Car_message::NAME = IfMessage::SIGNAME[1] = "sOut_Car";

if_sOut_Car_message::if_sOut_Car_message() 
  : IfMessage(if_sOut_Car_signal) {
  if_sOut_Car_par_reset(m_par);
}

if_sOut_Car_message::if_sOut_Car_message(if_pid_type p1,if_InfoZone_type p2) 
  : IfMessage(if_sOut_Car_signal) {
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
}

if_sOut_Car_message::if_sOut_Car_message(const if_sOut_Car_message& message) 
  : IfMessage(message) {
  if_sOut_Car_par_copy(m_par,message.m_par);
}

int if_sOut_Car_message::compare(const IfMessage* X) const {
  if_sOut_Car_message* x = (if_sOut_Car_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sOut_Car_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sOut_Car_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sOut_Car_message::copy() const {
  return new if_sOut_Car_message(*this);
}

void if_sOut_Car_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sOut_Car_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sOut_Car_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sOut_Car_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sOkInit message implementation 
 *
 */


inline void if_sOkInit_par_copy
    (if_sOkInit_par_type& x, const if_sOkInit_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_sOkInit_par_compare
    (const if_sOkInit_par_type x, const if_sOkInit_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_sOkInit_par_print
    (const if_sOkInit_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sOkInit_par_print_xml
    (const if_sOkInit_par_type x, std::ostream& b) { 
  b << "<sOkInit_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sOkInit_par>\n";
}
inline void if_sOkInit_par_reset
    (if_sOkInit_par_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_sOkInit_par_type if_sOkInit_par_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_sOkInit_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sOkInit_message::NAME = IfMessage::SIGNAME[2] = "sOkInit";

if_sOkInit_message::if_sOkInit_message() 
  : IfMessage(if_sOkInit_signal) {
  if_sOkInit_par_reset(m_par);
}

if_sOkInit_message::if_sOkInit_message(if_pid_type p1,if_InfoZone_type p2) 
  : IfMessage(if_sOkInit_signal) {
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
}

if_sOkInit_message::if_sOkInit_message(const if_sOkInit_message& message) 
  : IfMessage(message) {
  if_sOkInit_par_copy(m_par,message.m_par);
}

int if_sOkInit_message::compare(const IfMessage* X) const {
  if_sOkInit_message* x = (if_sOkInit_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sOkInit_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sOkInit_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sOkInit_message::copy() const {
  return new if_sOkInit_message(*this);
}

void if_sOkInit_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sOkInit_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sOkInit_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sOkInit_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sInfoZone message implementation 
 *
 */


inline void if_sInfoZone_par_copy
    (if_sInfoZone_par_type& x, const if_sInfoZone_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_InfoZone_copy(x.p2,y.p2);
}
inline int if_sInfoZone_par_compare
    (const if_sInfoZone_par_type x, const if_sInfoZone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_InfoZone_compare(x.p2,y.p2);
  return c;
}
inline void if_sInfoZone_par_print
    (const if_sInfoZone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_InfoZone_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sInfoZone_par_print_xml
    (const if_sInfoZone_par_type x, std::ostream& b) { 
  b << "<sInfoZone_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_InfoZone_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sInfoZone_par>\n";
}
inline void if_sInfoZone_par_reset
    (if_sInfoZone_par_type& x) {
  if_pid_reset(x.p1);
  if_InfoZone_reset(x.p2);
}

inline if_sInfoZone_par_type if_sInfoZone_par_make
    (if_pid_type p1,if_InfoZone_type p2) {
  if_sInfoZone_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sInfoZone_message::NAME = IfMessage::SIGNAME[3] = "sInfoZone";

if_sInfoZone_message::if_sInfoZone_message() 
  : IfMessage(if_sInfoZone_signal) {
  if_sInfoZone_par_reset(m_par);
}

if_sInfoZone_message::if_sInfoZone_message(if_pid_type p1,if_InfoZone_type p2) 
  : IfMessage(if_sInfoZone_signal) {
  if_pid_copy(m_par.p1,p1);
  if_InfoZone_copy(m_par.p2,p2);
}

if_sInfoZone_message::if_sInfoZone_message(const if_sInfoZone_message& message) 
  : IfMessage(message) {
  if_sInfoZone_par_copy(m_par,message.m_par);
}

int if_sInfoZone_message::compare(const IfMessage* X) const {
  if_sInfoZone_message* x = (if_sInfoZone_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sInfoZone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sInfoZone_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sInfoZone_message::copy() const {
  return new if_sInfoZone_message(*this);
}

void if_sInfoZone_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sInfoZone_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sInfoZone_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sInfoZone_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sInitFreeSpot message implementation 
 *
 */


inline void if_sInitFreeSpot_par_copy
    (if_sInitFreeSpot_par_type& x, const if_sInitFreeSpot_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_i_spots_copy(x.p2,y.p2);
}
inline int if_sInitFreeSpot_par_compare
    (const if_sInitFreeSpot_par_type x, const if_sInitFreeSpot_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_i_spots_compare(x.p2,y.p2);
  return c;
}
inline void if_sInitFreeSpot_par_print
    (const if_sInitFreeSpot_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_i_spots_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sInitFreeSpot_par_print_xml
    (const if_sInitFreeSpot_par_type x, std::ostream& b) { 
  b << "<sInitFreeSpot_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_i_spots_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sInitFreeSpot_par>\n";
}
inline void if_sInitFreeSpot_par_reset
    (if_sInitFreeSpot_par_type& x) {
  if_pid_reset(x.p1);
  if_i_spots_reset(x.p2);
}

inline if_sInitFreeSpot_par_type if_sInitFreeSpot_par_make
    (if_pid_type p1,if_i_spots_type p2) {
  if_sInitFreeSpot_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_i_spots_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sInitFreeSpot_message::NAME = IfMessage::SIGNAME[4] = "sInitFreeSpot";

if_sInitFreeSpot_message::if_sInitFreeSpot_message() 
  : IfMessage(if_sInitFreeSpot_signal) {
  if_sInitFreeSpot_par_reset(m_par);
}

if_sInitFreeSpot_message::if_sInitFreeSpot_message(if_pid_type p1,if_i_spots_type p2) 
  : IfMessage(if_sInitFreeSpot_signal) {
  if_pid_copy(m_par.p1,p1);
  if_i_spots_copy(m_par.p2,p2);
}

if_sInitFreeSpot_message::if_sInitFreeSpot_message(const if_sInitFreeSpot_message& message) 
  : IfMessage(message) {
  if_sInitFreeSpot_par_copy(m_par,message.m_par);
}

int if_sInitFreeSpot_message::compare(const IfMessage* X) const {
  if_sInitFreeSpot_message* x = (if_sInitFreeSpot_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sInitFreeSpot_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sInitFreeSpot_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sInitFreeSpot_message::copy() const {
  return new if_sInitFreeSpot_message(*this);
}

void if_sInitFreeSpot_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sInitFreeSpot_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sInitFreeSpot_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sInitFreeSpot_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sInitTotalSpots message implementation 
 *
 */


inline void if_sInitTotalSpots_par_copy
    (if_sInitTotalSpots_par_type& x, const if_sInitTotalSpots_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_i_spots_copy(x.p2,y.p2);
}
inline int if_sInitTotalSpots_par_compare
    (const if_sInitTotalSpots_par_type x, const if_sInitTotalSpots_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_i_spots_compare(x.p2,y.p2);
  return c;
}
inline void if_sInitTotalSpots_par_print
    (const if_sInitTotalSpots_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_i_spots_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sInitTotalSpots_par_print_xml
    (const if_sInitTotalSpots_par_type x, std::ostream& b) { 
  b << "<sInitTotalSpots_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_i_spots_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sInitTotalSpots_par>\n";
}
inline void if_sInitTotalSpots_par_reset
    (if_sInitTotalSpots_par_type& x) {
  if_pid_reset(x.p1);
  if_i_spots_reset(x.p2);
}

inline if_sInitTotalSpots_par_type if_sInitTotalSpots_par_make
    (if_pid_type p1,if_i_spots_type p2) {
  if_sInitTotalSpots_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_i_spots_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sInitTotalSpots_message::NAME = IfMessage::SIGNAME[5] = "sInitTotalSpots";

if_sInitTotalSpots_message::if_sInitTotalSpots_message() 
  : IfMessage(if_sInitTotalSpots_signal) {
  if_sInitTotalSpots_par_reset(m_par);
}

if_sInitTotalSpots_message::if_sInitTotalSpots_message(if_pid_type p1,if_i_spots_type p2) 
  : IfMessage(if_sInitTotalSpots_signal) {
  if_pid_copy(m_par.p1,p1);
  if_i_spots_copy(m_par.p2,p2);
}

if_sInitTotalSpots_message::if_sInitTotalSpots_message(const if_sInitTotalSpots_message& message) 
  : IfMessage(message) {
  if_sInitTotalSpots_par_copy(m_par,message.m_par);
}

int if_sInitTotalSpots_message::compare(const IfMessage* X) const {
  if_sInitTotalSpots_message* x = (if_sInitTotalSpots_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sInitTotalSpots_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sInitTotalSpots_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sInitTotalSpots_message::copy() const {
  return new if_sInitTotalSpots_message(*this);
}

void if_sInitTotalSpots_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sInitTotalSpots_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sInitTotalSpots_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sInitTotalSpots_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sReqInfo message implementation 
 *
 */


inline void if_sReqInfo_par_copy
    (if_sReqInfo_par_type& x, const if_sReqInfo_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sReqInfo_par_compare
    (const if_sReqInfo_par_type x, const if_sReqInfo_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sReqInfo_par_print
    (const if_sReqInfo_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sReqInfo_par_print_xml
    (const if_sReqInfo_par_type x, std::ostream& b) { 
  b << "<sReqInfo_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sReqInfo_par>\n";
}
inline void if_sReqInfo_par_reset
    (if_sReqInfo_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sReqInfo_par_type if_sReqInfo_par_make
    (if_pid_type p1) {
  if_sReqInfo_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sReqInfo_message::NAME = IfMessage::SIGNAME[6] = "sReqInfo";

if_sReqInfo_message::if_sReqInfo_message() 
  : IfMessage(if_sReqInfo_signal) {
  if_sReqInfo_par_reset(m_par);
}

if_sReqInfo_message::if_sReqInfo_message(if_pid_type p1) 
  : IfMessage(if_sReqInfo_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sReqInfo_message::if_sReqInfo_message(const if_sReqInfo_message& message) 
  : IfMessage(message) {
  if_sReqInfo_par_copy(m_par,message.m_par);
}

int if_sReqInfo_message::compare(const IfMessage* X) const {
  if_sReqInfo_message* x = (if_sReqInfo_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sReqInfo_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sReqInfo_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sReqInfo_message::copy() const {
  return new if_sReqInfo_message(*this);
}

void if_sReqInfo_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sReqInfo_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sReqInfo_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sReqInfo_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sLoopInductive_Zone message implementation 
 *
 */


inline void if_sLoopInductive_Zone_par_copy
    (if_sLoopInductive_Zone_par_type& x, const if_sLoopInductive_Zone_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sLoopInductive_Zone_par_compare
    (const if_sLoopInductive_Zone_par_type x, const if_sLoopInductive_Zone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sLoopInductive_Zone_par_print
    (const if_sLoopInductive_Zone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sLoopInductive_Zone_par_print_xml
    (const if_sLoopInductive_Zone_par_type x, std::ostream& b) { 
  b << "<sLoopInductive_Zone_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sLoopInductive_Zone_par>\n";
}
inline void if_sLoopInductive_Zone_par_reset
    (if_sLoopInductive_Zone_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sLoopInductive_Zone_par_type if_sLoopInductive_Zone_par_make
    (if_pid_type p1) {
  if_sLoopInductive_Zone_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sLoopInductive_Zone_message::NAME = IfMessage::SIGNAME[7] = "sLoopInductive_Zone";

if_sLoopInductive_Zone_message::if_sLoopInductive_Zone_message() 
  : IfMessage(if_sLoopInductive_Zone_signal) {
  if_sLoopInductive_Zone_par_reset(m_par);
}

if_sLoopInductive_Zone_message::if_sLoopInductive_Zone_message(if_pid_type p1) 
  : IfMessage(if_sLoopInductive_Zone_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sLoopInductive_Zone_message::if_sLoopInductive_Zone_message(const if_sLoopInductive_Zone_message& message) 
  : IfMessage(message) {
  if_sLoopInductive_Zone_par_copy(m_par,message.m_par);
}

int if_sLoopInductive_Zone_message::compare(const IfMessage* X) const {
  if_sLoopInductive_Zone_message* x = (if_sLoopInductive_Zone_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sLoopInductive_Zone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sLoopInductive_Zone_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sLoopInductive_Zone_message::copy() const {
  return new if_sLoopInductive_Zone_message(*this);
}

void if_sLoopInductive_Zone_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sLoopInductive_Zone_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sLoopInductive_Zone_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sLoopInductive_Zone_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sIR1_Zone message implementation 
 *
 */


inline void if_sIR1_Zone_par_copy
    (if_sIR1_Zone_par_type& x, const if_sIR1_Zone_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sIR1_Zone_par_compare
    (const if_sIR1_Zone_par_type x, const if_sIR1_Zone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sIR1_Zone_par_print
    (const if_sIR1_Zone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sIR1_Zone_par_print_xml
    (const if_sIR1_Zone_par_type x, std::ostream& b) { 
  b << "<sIR1_Zone_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sIR1_Zone_par>\n";
}
inline void if_sIR1_Zone_par_reset
    (if_sIR1_Zone_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sIR1_Zone_par_type if_sIR1_Zone_par_make
    (if_pid_type p1) {
  if_sIR1_Zone_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sIR1_Zone_message::NAME = IfMessage::SIGNAME[8] = "sIR1_Zone";

if_sIR1_Zone_message::if_sIR1_Zone_message() 
  : IfMessage(if_sIR1_Zone_signal) {
  if_sIR1_Zone_par_reset(m_par);
}

if_sIR1_Zone_message::if_sIR1_Zone_message(if_pid_type p1) 
  : IfMessage(if_sIR1_Zone_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sIR1_Zone_message::if_sIR1_Zone_message(const if_sIR1_Zone_message& message) 
  : IfMessage(message) {
  if_sIR1_Zone_par_copy(m_par,message.m_par);
}

int if_sIR1_Zone_message::compare(const IfMessage* X) const {
  if_sIR1_Zone_message* x = (if_sIR1_Zone_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sIR1_Zone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sIR1_Zone_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sIR1_Zone_message::copy() const {
  return new if_sIR1_Zone_message(*this);
}

void if_sIR1_Zone_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sIR1_Zone_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sIR1_Zone_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sIR1_Zone_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sIR2_Zone message implementation 
 *
 */


inline void if_sIR2_Zone_par_copy
    (if_sIR2_Zone_par_type& x, const if_sIR2_Zone_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sIR2_Zone_par_compare
    (const if_sIR2_Zone_par_type x, const if_sIR2_Zone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sIR2_Zone_par_print
    (const if_sIR2_Zone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sIR2_Zone_par_print_xml
    (const if_sIR2_Zone_par_type x, std::ostream& b) { 
  b << "<sIR2_Zone_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sIR2_Zone_par>\n";
}
inline void if_sIR2_Zone_par_reset
    (if_sIR2_Zone_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sIR2_Zone_par_type if_sIR2_Zone_par_make
    (if_pid_type p1) {
  if_sIR2_Zone_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sIR2_Zone_message::NAME = IfMessage::SIGNAME[9] = "sIR2_Zone";

if_sIR2_Zone_message::if_sIR2_Zone_message() 
  : IfMessage(if_sIR2_Zone_signal) {
  if_sIR2_Zone_par_reset(m_par);
}

if_sIR2_Zone_message::if_sIR2_Zone_message(if_pid_type p1) 
  : IfMessage(if_sIR2_Zone_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sIR2_Zone_message::if_sIR2_Zone_message(const if_sIR2_Zone_message& message) 
  : IfMessage(message) {
  if_sIR2_Zone_par_copy(m_par,message.m_par);
}

int if_sIR2_Zone_message::compare(const IfMessage* X) const {
  if_sIR2_Zone_message* x = (if_sIR2_Zone_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sIR2_Zone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sIR2_Zone_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sIR2_Zone_message::copy() const {
  return new if_sIR2_Zone_message(*this);
}

void if_sIR2_Zone_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sIR2_Zone_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sIR2_Zone_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sIR2_Zone_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sIR3_Zone message implementation 
 *
 */


inline void if_sIR3_Zone_par_copy
    (if_sIR3_Zone_par_type& x, const if_sIR3_Zone_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sIR3_Zone_par_compare
    (const if_sIR3_Zone_par_type x, const if_sIR3_Zone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sIR3_Zone_par_print
    (const if_sIR3_Zone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sIR3_Zone_par_print_xml
    (const if_sIR3_Zone_par_type x, std::ostream& b) { 
  b << "<sIR3_Zone_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sIR3_Zone_par>\n";
}
inline void if_sIR3_Zone_par_reset
    (if_sIR3_Zone_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sIR3_Zone_par_type if_sIR3_Zone_par_make
    (if_pid_type p1) {
  if_sIR3_Zone_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sIR3_Zone_message::NAME = IfMessage::SIGNAME[10] = "sIR3_Zone";

if_sIR3_Zone_message::if_sIR3_Zone_message() 
  : IfMessage(if_sIR3_Zone_signal) {
  if_sIR3_Zone_par_reset(m_par);
}

if_sIR3_Zone_message::if_sIR3_Zone_message(if_pid_type p1) 
  : IfMessage(if_sIR3_Zone_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sIR3_Zone_message::if_sIR3_Zone_message(const if_sIR3_Zone_message& message) 
  : IfMessage(message) {
  if_sIR3_Zone_par_copy(m_par,message.m_par);
}

int if_sIR3_Zone_message::compare(const IfMessage* X) const {
  if_sIR3_Zone_message* x = (if_sIR3_Zone_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sIR3_Zone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sIR3_Zone_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sIR3_Zone_message::copy() const {
  return new if_sIR3_Zone_message(*this);
}

void if_sIR3_Zone_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sIR3_Zone_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sIR3_Zone_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sIR3_Zone_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sIR4_Zone message implementation 
 *
 */


inline void if_sIR4_Zone_par_copy
    (if_sIR4_Zone_par_type& x, const if_sIR4_Zone_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sIR4_Zone_par_compare
    (const if_sIR4_Zone_par_type x, const if_sIR4_Zone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sIR4_Zone_par_print
    (const if_sIR4_Zone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sIR4_Zone_par_print_xml
    (const if_sIR4_Zone_par_type x, std::ostream& b) { 
  b << "<sIR4_Zone_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sIR4_Zone_par>\n";
}
inline void if_sIR4_Zone_par_reset
    (if_sIR4_Zone_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sIR4_Zone_par_type if_sIR4_Zone_par_make
    (if_pid_type p1) {
  if_sIR4_Zone_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sIR4_Zone_message::NAME = IfMessage::SIGNAME[11] = "sIR4_Zone";

if_sIR4_Zone_message::if_sIR4_Zone_message() 
  : IfMessage(if_sIR4_Zone_signal) {
  if_sIR4_Zone_par_reset(m_par);
}

if_sIR4_Zone_message::if_sIR4_Zone_message(if_pid_type p1) 
  : IfMessage(if_sIR4_Zone_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sIR4_Zone_message::if_sIR4_Zone_message(const if_sIR4_Zone_message& message) 
  : IfMessage(message) {
  if_sIR4_Zone_par_copy(m_par,message.m_par);
}

int if_sIR4_Zone_message::compare(const IfMessage* X) const {
  if_sIR4_Zone_message* x = (if_sIR4_Zone_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sIR4_Zone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sIR4_Zone_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sIR4_Zone_message::copy() const {
  return new if_sIR4_Zone_message(*this);
}

void if_sIR4_Zone_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sIR4_Zone_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sIR4_Zone_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sIR4_Zone_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sTemp message implementation 
 *
 */


inline void if_sTemp_par_copy
    (if_sTemp_par_type& x, const if_sTemp_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sTemp_par_compare
    (const if_sTemp_par_type x, const if_sTemp_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sTemp_par_print
    (const if_sTemp_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sTemp_par_print_xml
    (const if_sTemp_par_type x, std::ostream& b) { 
  b << "<sTemp_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sTemp_par>\n";
}
inline void if_sTemp_par_reset
    (if_sTemp_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sTemp_par_type if_sTemp_par_make
    (if_pid_type p1) {
  if_sTemp_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sTemp_message::NAME = IfMessage::SIGNAME[12] = "sTemp";

if_sTemp_message::if_sTemp_message() 
  : IfMessage(if_sTemp_signal) {
  if_sTemp_par_reset(m_par);
}

if_sTemp_message::if_sTemp_message(if_pid_type p1) 
  : IfMessage(if_sTemp_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sTemp_message::if_sTemp_message(const if_sTemp_message& message) 
  : IfMessage(message) {
  if_sTemp_par_copy(m_par,message.m_par);
}

int if_sTemp_message::compare(const IfMessage* X) const {
  if_sTemp_message* x = (if_sTemp_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sTemp_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sTemp_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sTemp_message::copy() const {
  return new if_sTemp_message(*this);
}

void if_sTemp_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sTemp_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sTemp_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sTemp_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sOkInitPid message implementation 
 *
 */


inline void if_sOkInitPid_par_copy
    (if_sOkInitPid_par_type& x, const if_sOkInitPid_par_type y) {
  if_pid_copy(x.p1,y.p1);
}
inline int if_sOkInitPid_par_compare
    (const if_sOkInitPid_par_type x, const if_sOkInitPid_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  return c;
}
inline void if_sOkInitPid_par_print
    (const if_sOkInitPid_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f);
  fprintf(f,"}");
}
inline void if_sOkInitPid_par_print_xml
    (const if_sOkInitPid_par_type x, std::ostream& b) { 
  b << "<sOkInitPid_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>"; 
  b << "</sOkInitPid_par>\n";
}
inline void if_sOkInitPid_par_reset
    (if_sOkInitPid_par_type& x) {
  if_pid_reset(x.p1);
}

inline if_sOkInitPid_par_type if_sOkInitPid_par_make
    (if_pid_type p1) {
  if_sOkInitPid_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  return m_par;
}

const char* if_sOkInitPid_message::NAME = IfMessage::SIGNAME[13] = "sOkInitPid";

if_sOkInitPid_message::if_sOkInitPid_message() 
  : IfMessage(if_sOkInitPid_signal) {
  if_sOkInitPid_par_reset(m_par);
}

if_sOkInitPid_message::if_sOkInitPid_message(if_pid_type p1) 
  : IfMessage(if_sOkInitPid_signal) {
  if_pid_copy(m_par.p1,p1);
}

if_sOkInitPid_message::if_sOkInitPid_message(const if_sOkInitPid_message& message) 
  : IfMessage(message) {
  if_sOkInitPid_par_copy(m_par,message.m_par);
}

int if_sOkInitPid_message::compare(const IfMessage* X) const {
  if_sOkInitPid_message* x = (if_sOkInitPid_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sOkInitPid_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sOkInitPid_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sOkInitPid_message::copy() const {
  return new if_sOkInitPid_message(*this);
}

void if_sOkInitPid_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sOkInitPid_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sOkInitPid_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sOkInitPid_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}


/*
 * sInitPidCtrl message implementation 
 *
 */


inline void if_sInitPidCtrl_par_copy
    (if_sInitPidCtrl_par_type& x, const if_sInitPidCtrl_par_type y) {
  if_pid_copy(x.p1,y.p1);
  if_pid_copy(x.p2,y.p2);
}
inline int if_sInitPidCtrl_par_compare
    (const if_sInitPidCtrl_par_type x, const if_sInitPidCtrl_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.p1,y.p1);
  if (c == 0) c = if_pid_compare(x.p2,y.p2);
  return c;
}
inline void if_sInitPidCtrl_par_print
    (const if_sInitPidCtrl_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"p1="); if_pid_print(x.p1,f); fprintf(f,",");
  fprintf(f,"p2="); if_pid_print(x.p2,f);
  fprintf(f,"}");
}
inline void if_sInitPidCtrl_par_print_xml
    (const if_sInitPidCtrl_par_type x, std::ostream& b) { 
  b << "<sInitPidCtrl_par>\n";
  b << "<p1>"; if_pid_print_xml(x.p1,b); b << "</p1>";
  b << "<p2>"; if_pid_print_xml(x.p2,b); b << "</p2>"; 
  b << "</sInitPidCtrl_par>\n";
}
inline void if_sInitPidCtrl_par_reset
    (if_sInitPidCtrl_par_type& x) {
  if_pid_reset(x.p1);
  if_pid_reset(x.p2);
}

inline if_sInitPidCtrl_par_type if_sInitPidCtrl_par_make
    (if_pid_type p1,if_pid_type p2) {
  if_sInitPidCtrl_par_type m_par;
  if_pid_copy(m_par.p1,p1);
  if_pid_copy(m_par.p2,p2);
  return m_par;
}

const char* if_sInitPidCtrl_message::NAME = IfMessage::SIGNAME[14] = "sInitPidCtrl";

if_sInitPidCtrl_message::if_sInitPidCtrl_message() 
  : IfMessage(if_sInitPidCtrl_signal) {
  if_sInitPidCtrl_par_reset(m_par);
}

if_sInitPidCtrl_message::if_sInitPidCtrl_message(if_pid_type p1,if_pid_type p2) 
  : IfMessage(if_sInitPidCtrl_signal) {
  if_pid_copy(m_par.p1,p1);
  if_pid_copy(m_par.p2,p2);
}

if_sInitPidCtrl_message::if_sInitPidCtrl_message(const if_sInitPidCtrl_message& message) 
  : IfMessage(message) {
  if_sInitPidCtrl_par_copy(m_par,message.m_par);
}

int if_sInitPidCtrl_message::compare(const IfMessage* X) const {
  if_sInitPidCtrl_message* x = (if_sInitPidCtrl_message*)X;
  int cmp = IfMessage::compare(X);
  if (cmp == 0) cmp = if_sInitPidCtrl_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_sInitPidCtrl_message::hash(const unsigned long base) const {
  unsigned long key = IfMessage::hash(base);
  if (sizeof(m_par) >= 4) // void
    key += 17 * if_hash((char*) &m_par, sizeof(m_par), base);
  return key % base;
}

IfMessage* if_sInitPidCtrl_message::copy() const {
  return new if_sInitPidCtrl_message(*this);
}

void if_sInitPidCtrl_message::print(FILE* f) const {
  fprintf(f, "%s", NAME);
  if_sInitPidCtrl_par_print(m_par,f);
  IfMessage::print(f);
}

void if_sInitPidCtrl_message::printXML(std::ostream& buf) const {
  buf << "<IfMessage ";
  buf << "type=\"" << NAME << "\">\n";	    

  buf << "<par>\n";	    
  if_sInitPidCtrl_par_print_xml(m_par,buf);
  buf << "</par>\n";	    

  IfMessage::printXML(buf);
  buf << "</IfMessage>\n";
}













/* 
 * ParkingSystem [system] instance implementation 
 *
 */

if_ParkingSystem_instance::if_ParkingSystem_instance(if_pid_type pid, IfQueue* queue) 
  : IfInstance(pid, queue) {
} 

if_ParkingSystem_instance::if_ParkingSystem_instance(const if_ParkingSystem_instance& instance) 
  : IfInstance(instance) {
}




/* 
 * pZone instance implementation 
 *
 */


inline void if_pZone_par_copy
    (if_pZone_par_type& x, const if_pZone_par_type y) {
  if_pid_copy(x.PARENT,y.PARENT);
}
inline int if_pZone_par_compare
    (const if_pZone_par_type x, const if_pZone_par_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.PARENT,y.PARENT);
  return c;
}
inline void if_pZone_par_print
    (const if_pZone_par_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"PARENT="); if_pid_print(x.PARENT,f);
  fprintf(f,"}");
}
inline void if_pZone_par_print_xml
    (const if_pZone_par_type x, std::ostream& b) { 
  b << "<pZone_par>\n";
  b << "<PARENT>"; if_pid_print_xml(x.PARENT,b); b << "</PARENT>"; 
  b << "</pZone_par>\n";
}
inline void if_pZone_par_reset
    (if_pZone_par_type& x) {
  if_pid_reset(x.PARENT);
}

inline if_pZone_par_type if_pZone_par_make
    (if_pid_type PARENT) {
  if_pZone_par_type m_par;
  if_pid_copy(m_par.PARENT,PARENT);
  return m_par;
}


inline void if_pZone_var_copy
    (if_pZone_var_type& x, const if_pZone_var_type y) {
  if_pid_copy(x.OFFSPRING,y.OFFSPRING);
  if_pid_copy(x.SENDER,y.SENDER);
  if_boolean_copy(x.RTDS_skip,y.RTDS_skip);
  if_boolean_copy(x.RTDS_stop,y.RTDS_stop);
  if_i_spots_copy(x.p_freeSpots,y.p_freeSpots);
  if_i_spots_copy(x.p_totalSpots,y.p_totalSpots);
  if_i_spots_copy(x.TmpfreeSpots,y.TmpfreeSpots);
  if_i_spots_copy(x.TmptotalSpots,y.TmptotalSpots);
  if_i_spots_copy(x.freeSpots,y.freeSpots);
  if_i_spots_copy(x.totalSpots,y.totalSpots);
  if_pid_copy(x.PidZone,y.PidZone);
  if_pid_copy(x.pid_Ctrl,y.pid_Ctrl);
  if_pid_copy(x.pidCtrl,y.pidCtrl);
  if_InfoZone_copy(x.infoTableZone,y.infoTableZone);
}
inline int if_pZone_var_compare
    (const if_pZone_var_type x, const if_pZone_var_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.OFFSPRING,y.OFFSPRING);
  if (c == 0) c = if_pid_compare(x.SENDER,y.SENDER);
  if (c == 0) c = if_boolean_compare(x.RTDS_skip,y.RTDS_skip);
  if (c == 0) c = if_boolean_compare(x.RTDS_stop,y.RTDS_stop);
  if (c == 0) c = if_i_spots_compare(x.p_freeSpots,y.p_freeSpots);
  if (c == 0) c = if_i_spots_compare(x.p_totalSpots,y.p_totalSpots);
  if (c == 0) c = if_i_spots_compare(x.TmpfreeSpots,y.TmpfreeSpots);
  if (c == 0) c = if_i_spots_compare(x.TmptotalSpots,y.TmptotalSpots);
  if (c == 0) c = if_i_spots_compare(x.freeSpots,y.freeSpots);
  if (c == 0) c = if_i_spots_compare(x.totalSpots,y.totalSpots);
  if (c == 0) c = if_pid_compare(x.PidZone,y.PidZone);
  if (c == 0) c = if_pid_compare(x.pid_Ctrl,y.pid_Ctrl);
  if (c == 0) c = if_pid_compare(x.pidCtrl,y.pidCtrl);
  if (c == 0) c = if_InfoZone_compare(x.infoTableZone,y.infoTableZone);
  return c;
}
inline void if_pZone_var_print
    (const if_pZone_var_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"OFFSPRING="); if_pid_print(x.OFFSPRING,f); fprintf(f,",");
  fprintf(f,"SENDER="); if_pid_print(x.SENDER,f); fprintf(f,",");
  fprintf(f,"RTDS_skip="); if_boolean_print(x.RTDS_skip,f); fprintf(f,",");
  fprintf(f,"RTDS_stop="); if_boolean_print(x.RTDS_stop,f); fprintf(f,",");
  fprintf(f,"p_freeSpots="); if_i_spots_print(x.p_freeSpots,f); fprintf(f,",");
  fprintf(f,"p_totalSpots="); if_i_spots_print(x.p_totalSpots,f); fprintf(f,",");
  fprintf(f,"TmpfreeSpots="); if_i_spots_print(x.TmpfreeSpots,f); fprintf(f,",");
  fprintf(f,"TmptotalSpots="); if_i_spots_print(x.TmptotalSpots,f); fprintf(f,",");
  fprintf(f,"freeSpots="); if_i_spots_print(x.freeSpots,f); fprintf(f,",");
  fprintf(f,"totalSpots="); if_i_spots_print(x.totalSpots,f); fprintf(f,",");
  fprintf(f,"PidZone="); if_pid_print(x.PidZone,f); fprintf(f,",");
  fprintf(f,"pid_Ctrl="); if_pid_print(x.pid_Ctrl,f); fprintf(f,",");
  fprintf(f,"pidCtrl="); if_pid_print(x.pidCtrl,f); fprintf(f,",");
  fprintf(f,"infoTableZone="); if_InfoZone_print(x.infoTableZone,f);
  fprintf(f,"}");
}
inline void if_pZone_var_print_xml
    (const if_pZone_var_type x, std::ostream& b) { 
  b << "<pZone_var>\n";
  b << "<OFFSPRING>"; if_pid_print_xml(x.OFFSPRING,b); b << "</OFFSPRING>";
  b << "<SENDER>"; if_pid_print_xml(x.SENDER,b); b << "</SENDER>";
  b << "<RTDS_skip>"; if_boolean_print_xml(x.RTDS_skip,b); b << "</RTDS_skip>";
  b << "<RTDS_stop>"; if_boolean_print_xml(x.RTDS_stop,b); b << "</RTDS_stop>";
  b << "<p_freeSpots>"; if_i_spots_print_xml(x.p_freeSpots,b); b << "</p_freeSpots>";
  b << "<p_totalSpots>"; if_i_spots_print_xml(x.p_totalSpots,b); b << "</p_totalSpots>";
  b << "<TmpfreeSpots>"; if_i_spots_print_xml(x.TmpfreeSpots,b); b << "</TmpfreeSpots>";
  b << "<TmptotalSpots>"; if_i_spots_print_xml(x.TmptotalSpots,b); b << "</TmptotalSpots>";
  b << "<freeSpots>"; if_i_spots_print_xml(x.freeSpots,b); b << "</freeSpots>";
  b << "<totalSpots>"; if_i_spots_print_xml(x.totalSpots,b); b << "</totalSpots>";
  b << "<PidZone>"; if_pid_print_xml(x.PidZone,b); b << "</PidZone>";
  b << "<pid_Ctrl>"; if_pid_print_xml(x.pid_Ctrl,b); b << "</pid_Ctrl>";
  b << "<pidCtrl>"; if_pid_print_xml(x.pidCtrl,b); b << "</pidCtrl>";
  b << "<infoTableZone>"; if_InfoZone_print_xml(x.infoTableZone,b); b << "</infoTableZone>"; 
  b << "</pZone_var>\n";
}
inline void if_pZone_var_reset
    (if_pZone_var_type& x) {
  if_pid_reset(x.OFFSPRING);
  if_pid_reset(x.SENDER);
  if_boolean_reset(x.RTDS_skip);
  if_boolean_reset(x.RTDS_stop);
  if_i_spots_reset(x.p_freeSpots);
  if_i_spots_reset(x.p_totalSpots);
  if_i_spots_reset(x.TmpfreeSpots);
  if_i_spots_reset(x.TmptotalSpots);
  if_i_spots_reset(x.freeSpots);
  if_i_spots_reset(x.totalSpots);
  if_pid_reset(x.PidZone);
  if_pid_reset(x.pid_Ctrl);
  if_pid_reset(x.pidCtrl);
  if_InfoZone_reset(x.infoTableZone);
}

inline if_pZone_var_type if_pZone_var_make
    (if_pid_type OFFSPRING,if_pid_type SENDER,if_boolean_type RTDS_skip,if_boolean_type RTDS_stop,if_i_spots_type p_freeSpots,if_i_spots_type p_totalSpots,if_i_spots_type TmpfreeSpots,if_i_spots_type TmptotalSpots,if_i_spots_type freeSpots,if_i_spots_type totalSpots,if_pid_type PidZone,if_pid_type pid_Ctrl,if_pid_type pidCtrl,if_InfoZone_type infoTableZone) {
  if_pZone_var_type m_par;
  if_pid_copy(m_par.OFFSPRING,OFFSPRING);
  if_pid_copy(m_par.SENDER,SENDER);
  if_boolean_copy(m_par.RTDS_skip,RTDS_skip);
  if_boolean_copy(m_par.RTDS_stop,RTDS_stop);
  if_i_spots_copy(m_par.p_freeSpots,p_freeSpots);
  if_i_spots_copy(m_par.p_totalSpots,p_totalSpots);
  if_i_spots_copy(m_par.TmpfreeSpots,TmpfreeSpots);
  if_i_spots_copy(m_par.TmptotalSpots,TmptotalSpots);
  if_i_spots_copy(m_par.freeSpots,freeSpots);
  if_i_spots_copy(m_par.totalSpots,totalSpots);
  if_pid_copy(m_par.PidZone,PidZone);
  if_pid_copy(m_par.pid_Ctrl,pid_Ctrl);
  if_pid_copy(m_par.pidCtrl,pidCtrl);
  if_InfoZone_copy(m_par.infoTableZone,infoTableZone);
  return m_par;
}


inline void if_pZone_ctl_copy
    (if_pZone_ctl_type& x, const if_pZone_ctl_type y) {
  if_integer_copy(x.top,y.top);
}
inline int if_pZone_ctl_compare
    (const if_pZone_ctl_type x, const if_pZone_ctl_type y) {
  int c = 0;
  if (c == 0) c = if_integer_compare(x.top,y.top);
  return c;
}
inline void if_pZone_ctl_print
    (const if_pZone_ctl_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"top="); if_integer_print(x.top,f);
  fprintf(f,"}");
}
inline void if_pZone_ctl_print_xml
    (const if_pZone_ctl_type x, std::ostream& b) { 
  b << "<pZone_ctl>\n";
  b << "<top>"; if_integer_print_xml(x.top,b); b << "</top>"; 
  b << "</pZone_ctl>\n";
}
inline void if_pZone_ctl_reset
    (if_pZone_ctl_type& x) {
  if_integer_reset(x.top);
}

inline if_pZone_ctl_type if_pZone_ctl_make
    (if_integer_type top) {
  if_pZone_ctl_type m_par;
  if_integer_copy(m_par.top,top);
  return m_par;
}

const char* if_pZone_instance::NAME = IfInstance::PROCNAME[10] = "pZone";

if_pZone_instance::if_pZone_instance() 
  : if_ParkingSystem_instance(if_pid_mk(if_pZone_process,0), IfQueue::NIL) {
  m_ctl.top=-1;
  m_ctl.top=1;
  
    STATUS |=  CREATE;
  if_pZone_var_reset(m_var);
  if_pZone_par_reset(m_par);
    STATUS &= ~CREATE;
  
}

if_pZone_instance::if_pZone_instance(if_pid_type PARENT) 
  : if_ParkingSystem_instance(if_pid_mk(if_pZone_process,0), IfQueue::NIL) {
  m_ctl.top=-1;
  m_ctl.top=1;
  
    STATUS |=  CREATE;
  if_pZone_var_reset(m_var);
  
    STATUS &= ~CREATE;
  
  if_pid_copy(m_par.PARENT,PARENT);
}

if_pZone_instance::if_pZone_instance(const if_pZone_instance& instance) 
  : if_ParkingSystem_instance(instance) {
  if_pZone_ctl_copy(m_ctl,instance.m_ctl);
  if_pZone_var_copy(m_var,instance.m_var);
  if_pZone_par_copy(m_par,instance.m_par);
}

const char* if_pZone_instance::getState() const {
  static char r[1024];
  char tmp[256];
  *r = (char)0;
  if(m_ctl.top != -1) { sprintf(tmp,"top:%s,", STATE[m_ctl.top].name); strcat(r,tmp); }
  
  r[strlen(r)-1]=(char)0;
  return r;
}

int if_pZone_instance::is(const unsigned flag) const {
  int ok = 0;
  if (m_ctl.top != -1)
    ok |= (STATE[m_ctl.top].flags & flag);
  return ok;
}

int if_pZone_instance::compare(const IfInstance* X) const {
  if_pZone_instance* x = (if_pZone_instance*)X;
  int cmp = IfInstance::compare(X);
  if (cmp == 0) cmp = if_pZone_ctl_compare(m_ctl,x->m_ctl);
  if (cmp == 0) cmp = if_pZone_var_compare(m_var,x->m_var);
  if (cmp == 0) cmp = if_pZone_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_pZone_instance::hash(const unsigned long base) const {
  unsigned long key = m_pid;
  key += (unsigned long) m_queue; 
  if (sizeof(m_var) >= 4) // void 
    key += if_hash((char*) &m_var, sizeof(m_var), base);
  if (sizeof(m_par) >= 4) // void
    key += if_hash((char*) &m_par, sizeof(m_par), base);
  key += if_hash((char*) &m_ctl, sizeof(m_ctl), base);
  return key % base;
}

IfInstance* if_pZone_instance::copy() const {
  return new if_pZone_instance(*this);
}

void if_pZone_instance::print(FILE* f) const {
  // warning: print the topmost state name only
  IfInstance::print(f);
  fprintf(f, "\n  @%s\t\t", getState());
  if_pZone_var_print(m_var,f);
  fprintf(f, " ");
  if_pZone_par_print(m_par,f);
}

void if_pZone_instance::printXML(std::ostream& buf) const {
  buf << "<IfInstance ";
  buf << "type=\"pZone\" ";
  buf << "state=\"" << getState() << "\" >\n";    
  IfInstance::printXML(buf);

  buf << "<var>\n";     
  if_pZone_var_print_xml(m_var,buf);
  buf << "</var>\n";        

  buf << "<par>\n";     
  if_pZone_par_print_xml(m_par,buf);
  buf << "</par>\n";        
  buf << "</IfInstance>\n";   
}

void if_pZone_instance::copy(const IfInstance* X) {
  if_pZone_instance* x = (if_pZone_instance*) X;
  IfInstance::copy(X);
  if_pZone_ctl_copy(m_ctl,x->m_ctl);
  if_pZone_var_copy(m_var,x->m_var);
  if_pZone_par_copy(m_par,x->m_par);
}

void if_pZone_instance::reset() {
  if_pZone_ctl_reset(m_ctl);
  m_ctl.top=-1;
  m_ctl.top=1;
  
  if_pZone_var_reset(m_var);
  if_pZone_par_reset(m_par);
}

void if_pZone_instance::iterate(IfIterator* iterator) {
  STEP = 0;
  ITERATOR = iterator;
  fire();
  ITERATOR = NULL;
}


void if_pZone_instance::fire() {
  unsigned step = STEP;

// CS: no DISCARD since it complicates everything
//  if (opt_discard && (STATE[m_sp].flags & STABLE)) {
//    IfMessage* message = NULL;
//    for(IfQueue* queue = m_queue; 
//        queue != IfQueue::NIL; 
//        queue = (IfQueue*) queue->getTail()) {
//      message = (IfMessage*) queue->getHead();
//      if (!save(message->getSid()))
//        break;
//      message = NULL;
//    }
//    if (message != NULL) {
//      m_queue = m_queue->remove(message);
//      if (STATE[m_sp].flags & TSIG) {
//        ITERATOR->record();
//        (this->*(STATE[m_sp].dispatch))(message);
//        ITERATOR->forget();
//      }
//      if(STEP == step) {
//        IfTime::Constraint constraints[] = {{0,0,0}};
//        ITERATOR->guard(constraints,EAGER);      
//        ITERATOR->trace(IfEvent::DISCARD, m_pid, message->string(), m_pid, message->store());
//        nextstate(-1);
//      }
//    }
//    ITERATOR->restore();
//  } else {

  int unstable = is(UNSTABLE);

  if ( is(TSIG) ) {
    IfMessage* message = NULL;
    for(IfQueue* queue = m_queue; 
        queue != IfQueue::NIL; 
        queue = (IfQueue*) queue->getTail()) {
      message = (IfMessage*) queue->getHead();
      if (!save(message->getSid()))
        break;
      message = NULL;
    }
    if (message != NULL) {
      m_queue = m_queue->remove(message);
      ITERATOR->record();
      dispatch(message, unstable);
      ITERATOR->forget();
    }
    ITERATOR->restore();
  }
//  }
  if ( is(TNONE) )
    dispatch(NULL, unstable);
  if ( is(TSIG) ) {
        if (input(if_sIR1_Zone_signal) && !save(if_sIR1_Zone_signal)) {
      if_sIR1_Zone_message x;
      if_sIR1_Zone_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sInitTotalSpots_signal) && !save(if_sInitTotalSpots_signal)) {
      if_sInitTotalSpots_message x;
      if_sInitTotalSpots_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sIR2_Zone_signal) && !save(if_sIR2_Zone_signal)) {
      if_sIR2_Zone_message x;
      if_sIR2_Zone_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sInitPidCtrl_signal) && !save(if_sInitPidCtrl_signal)) {
      if_sInitPidCtrl_message x;
      if_sInitPidCtrl_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sLoopInductive_Zone_signal) && !save(if_sLoopInductive_Zone_signal)) {
      if_sLoopInductive_Zone_message x;
      if_sLoopInductive_Zone_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sReqInfo_signal) && !save(if_sReqInfo_signal)) {
      if_sReqInfo_message x;
      if_sReqInfo_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sIR4_Zone_signal) && !save(if_sIR4_Zone_signal)) {
      if_sIR4_Zone_message x;
      if_sIR4_Zone_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sIR3_Zone_signal) && !save(if_sIR3_Zone_signal)) {
      if_sIR3_Zone_message x;
      if_sIR3_Zone_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
        if (input(if_sInitFreeSpot_signal) && !save(if_sInitFreeSpot_signal)) {
      if_sInitFreeSpot_message x;
      if_sInitFreeSpot_par_iterate(x.m_par)
        dispatch(&x,unstable);
    }
    
  }

  if (is(UNSTABLE) && step == STEP)
      fprintf(stderr, "\nerror #2: unstable deadlock: %s@%s\n", 
          NAME, getState());
}

void if_pZone_instance::dispatch(IfMessage* message, int unstable) {
  if (m_ctl.top != -1 && (int)(STATE[m_ctl.top].flags & UNSTABLE) == unstable)
    (this->*(STATE[m_ctl.top].dispatch))(message);
  
}

void if_pZone_instance::nextstate() {

  if ( !is(UNSTABLE) )
    ITERATOR->step();
  else {
    ITERATOR->record();
    fire();
    ITERATOR->forget();
  }
}



void if_pZone_instance::_top_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  
}

void if_pZone_instance::_RTDS_START_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _RTDS_START_1_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_pZone_instance::_RTDS_START_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_boolean_true))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "141"); 
  
    _RTDS_START_1a_fire();
    _RTDS_START_1b_fire();
    _RTDS_START_1c_fire();
    _RTDS_START_1d_fire();
    _RTDS_START_1e_fire();

  
  _RTDS_START_1f_fire();
  
}
inline void if_pZone_instance::_RTDS_START_1a_fire() {

  if_pid_copy(m_var.PidZone,m_pid);
}
inline void if_pZone_instance::_RTDS_START_1b_fire() {

  if_pid_copy(m_var.infoTableZone.ID,m_var.PidZone);
}
inline void if_pZone_instance::_RTDS_START_1c_fire() {

  if_i_spots_copy(m_var.infoTableZone.freeSpots,2);
}
inline void if_pZone_instance::_RTDS_START_1d_fire() {

  if_i_spots_copy(m_var.infoTableZone.totalSpots,2);
}
inline void if_pZone_instance::_RTDS_START_1e_fire() {

  if_sTemp_message x(m_pid);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_RTDS_START_1f_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}


void if_pZone_instance::_sWait_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _sWait_1_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_pZone_instance::_sWait_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_boolean_true))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "152"); 
  
    _sWait_1a_fire();

  
  _sWait_1b_fire();
  
}
inline void if_pZone_instance::_sWait_1a_fire() {

  if_sOkInitPid_message x(m_pid);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_sWait_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=2;
  
  nextstate();
}


void if_pZone_instance::_Idle_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    case if_sReqInfo_signal:
      _Idle_1_fire(message);
      ITERATOR->restore();
      break;
    case if_sIR1_Zone_signal:
      _Idle_2_fire(message);
      ITERATOR->restore();
      break;
    case if_sInitPidCtrl_signal:
      _Idle_3_fire(message);
      ITERATOR->restore();
      break;
    case if_sInitFreeSpot_signal:
      _Idle_4_fire(message);
      ITERATOR->restore();
      break;
    case if_sIR3_Zone_signal:
      _Idle_5_fire(message);
      ITERATOR->restore();
      break;
    case if_sInitTotalSpots_signal:
      _Idle_6_fire(message);
      ITERATOR->restore();
      break;
    }
  _top_dispatch(message);
}

void if_pZone_instance::_Idle_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "161"); 
  _Idle_1a_fire(X);
    _Idle_1b_fire();

  
  _Idle_1c_fire();
  
}
inline void if_pZone_instance::_Idle_1a_fire(IfMessage* X) {

  if_sReqInfo_message* x = (if_sReqInfo_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}
inline void if_pZone_instance::_Idle_1b_fire() {

  if_sInfoZone_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_Idle_1c_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}

void if_pZone_instance::_Idle_2_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "166"); 
  _Idle_2a_fire(X);

  
  _Idle_2b_fire();
  
}
inline void if_pZone_instance::_Idle_2a_fire(IfMessage* X) {

  if_sIR1_Zone_message* x = (if_sIR1_Zone_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}

inline void if_pZone_instance::_Idle_2b_fire() {

  m_ctl.top=-1;
  m_ctl.top=5;
  
  nextstate();
}

void if_pZone_instance::_Idle_3_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "170"); 
  _Idle_3a_fire(X);
    _Idle_3b_fire();

  
  _Idle_3c_fire();
  
}
inline void if_pZone_instance::_Idle_3a_fire(IfMessage* X) {

  if_sInitPidCtrl_message* x = (if_sInitPidCtrl_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  if_pid_copy(m_var.pidCtrl,x->m_par.p2);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}
inline void if_pZone_instance::_Idle_3b_fire() {

  if_pid_copy(m_var.pid_Ctrl,m_var.pidCtrl);
}
inline void if_pZone_instance::_Idle_3c_fire() {

  m_ctl.top=-1;
  m_ctl.top=2;
  
  nextstate();
}

void if_pZone_instance::_Idle_4_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "175"); 
  _Idle_4a_fire(X);
    _Idle_4b_fire();
    _Idle_4c_fire();

  
  _Idle_4d_fire();
  
}
inline void if_pZone_instance::_Idle_4a_fire(IfMessage* X) {

  if_sInitFreeSpot_message* x = (if_sInitFreeSpot_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  if_i_spots_copy(m_var.p_freeSpots,x->m_par.p2);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}
inline void if_pZone_instance::_Idle_4b_fire() {

  if_i_spots_copy(m_var.infoTableZone.freeSpots,m_var.p_freeSpots);
}
inline void if_pZone_instance::_Idle_4c_fire() {

  if_sOkInit_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_Idle_4d_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}

void if_pZone_instance::_Idle_5_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "181"); 
  _Idle_5a_fire(X);

  
  _Idle_5b_fire();
  
}
inline void if_pZone_instance::_Idle_5a_fire(IfMessage* X) {

  if_sIR3_Zone_message* x = (if_sIR3_Zone_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}

inline void if_pZone_instance::_Idle_5b_fire() {

  m_ctl.top=-1;
  m_ctl.top=4;
  
  nextstate();
}

void if_pZone_instance::_Idle_6_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "185"); 
  _Idle_6a_fire(X);
    _Idle_6b_fire();
    _Idle_6c_fire();

  
  _Idle_6d_fire();
  
}
inline void if_pZone_instance::_Idle_6a_fire(IfMessage* X) {

  if_sInitTotalSpots_message* x = (if_sInitTotalSpots_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  if_i_spots_copy(m_var.p_totalSpots,x->m_par.p2);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}
inline void if_pZone_instance::_Idle_6b_fire() {

  if_i_spots_copy(m_var.infoTableZone.totalSpots,m_var.p_totalSpots);
}
inline void if_pZone_instance::_Idle_6c_fire() {

  if_sOkInit_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_Idle_6d_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}


void if_pZone_instance::_WaitSensorIR4_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    case if_sIR4_Zone_signal:
      _WaitSensorIR4_1_fire(message);
      ITERATOR->restore();
      break;
    }
  _top_dispatch(message);
}

void if_pZone_instance::_WaitSensorIR4_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "195"); 
  _WaitSensorIR4_1a_fire(X);

  
  _WaitSensorIR4_1b_fire();
  
}
inline void if_pZone_instance::_WaitSensorIR4_1a_fire(IfMessage* X) {

  if_sIR4_Zone_message* x = (if_sIR4_Zone_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}

inline void if_pZone_instance::_WaitSensorIR4_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=9;
  
  nextstate();
}


void if_pZone_instance::_WaitSensorIR2_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    case if_sIR2_Zone_signal:
      _WaitSensorIR2_1_fire(message);
      ITERATOR->restore();
      break;
    }
  _top_dispatch(message);
}

void if_pZone_instance::_WaitSensorIR2_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "203"); 
  _WaitSensorIR2_1a_fire(X);

  
  _WaitSensorIR2_1b_fire();
  
}
inline void if_pZone_instance::_WaitSensorIR2_1a_fire(IfMessage* X) {

  if_sIR2_Zone_message* x = (if_sIR2_Zone_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}

inline void if_pZone_instance::_WaitSensorIR2_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=7;
  
  nextstate();
}


void if_pZone_instance::_sEvaluatingFreeSpots_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _sEvaluatingFreeSpots_1_fire(message);
      ITERATOR->restore();
      _sEvaluatingFreeSpots_2_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_pZone_instance::_sEvaluatingFreeSpots_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_integer_eq(m_var.TmpfreeSpots,0)))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "209"); 
  
    _sEvaluatingFreeSpots_1a_fire();

  
  _sEvaluatingFreeSpots_1b_fire();
  
}
inline void if_pZone_instance::_sEvaluatingFreeSpots_1a_fire() {

  if_sEntered_Car_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_sEvaluatingFreeSpots_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}

void if_pZone_instance::_sEvaluatingFreeSpots_2_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_integer_gt(m_var.TmpfreeSpots,0)))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "212"); 
  
    _sEvaluatingFreeSpots_2a_fire();
    _sEvaluatingFreeSpots_2b_fire();
    _sEvaluatingFreeSpots_2c_fire();

  
  _sEvaluatingFreeSpots_2d_fire();
  
}
inline void if_pZone_instance::_sEvaluatingFreeSpots_2a_fire() {

  if_i_spots_copy(m_var.TmpfreeSpots,if_integer_minus(m_var.TmpfreeSpots,1));
}
inline void if_pZone_instance::_sEvaluatingFreeSpots_2b_fire() {

  if_i_spots_copy(m_var.infoTableZone.freeSpots,m_var.TmpfreeSpots);
}
inline void if_pZone_instance::_sEvaluatingFreeSpots_2c_fire() {

  if_sEntered_Car_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_sEvaluatingFreeSpots_2d_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}


void if_pZone_instance::_VerifyIsaCarEntering_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    case if_sLoopInductive_Zone_signal:
      _VerifyIsaCarEntering_1_fire(message);
      ITERATOR->restore();
      break;
    }
  _top_dispatch(message);
}

void if_pZone_instance::_VerifyIsaCarEntering_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "223"); 
  _VerifyIsaCarEntering_1a_fire(X);
    _VerifyIsaCarEntering_1b_fire();

  
  _VerifyIsaCarEntering_1c_fire();
  
}
inline void if_pZone_instance::_VerifyIsaCarEntering_1a_fire(IfMessage* X) {

  if_sLoopInductive_Zone_message* x = (if_sLoopInductive_Zone_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}
inline void if_pZone_instance::_VerifyIsaCarEntering_1b_fire() {

  if_i_spots_copy(m_var.TmpfreeSpots,m_var.infoTableZone.freeSpots);
}
inline void if_pZone_instance::_VerifyIsaCarEntering_1c_fire() {

  m_ctl.top=-1;
  m_ctl.top=6;
  
  nextstate();
}


void if_pZone_instance::_sEvaluatingTotalSpots_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _sEvaluatingTotalSpots_1_fire(message);
      ITERATOR->restore();
      _sEvaluatingTotalSpots_2_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_pZone_instance::_sEvaluatingTotalSpots_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_integer_eq(m_var.TmpfreeSpots,m_var.TmptotalSpots)))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "230"); 
  
    _sEvaluatingTotalSpots_1a_fire();

  
  _sEvaluatingTotalSpots_1b_fire();
  
}
inline void if_pZone_instance::_sEvaluatingTotalSpots_1a_fire() {

  if_sOut_Car_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_sEvaluatingTotalSpots_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}

void if_pZone_instance::_sEvaluatingTotalSpots_2_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_integer_lt(m_var.TmpfreeSpots,m_var.TmptotalSpots)))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "233"); 
  
    _sEvaluatingTotalSpots_2a_fire();
    _sEvaluatingTotalSpots_2b_fire();
    _sEvaluatingTotalSpots_2c_fire();

  
  _sEvaluatingTotalSpots_2d_fire();
  
}
inline void if_pZone_instance::_sEvaluatingTotalSpots_2a_fire() {

  if_i_spots_copy(m_var.TmpfreeSpots,if_integer_plus(m_var.TmpfreeSpots,1));
}
inline void if_pZone_instance::_sEvaluatingTotalSpots_2b_fire() {

  if_i_spots_copy(m_var.infoTableZone.freeSpots,m_var.TmpfreeSpots);
}
inline void if_pZone_instance::_sEvaluatingTotalSpots_2c_fire() {

  if_sOut_Car_message x(m_pid,m_var.infoTableZone);
  
  ITERATOR->trace(IfEvent::OUTPUT, m_pid, x.string(), 0, x.store()); // anticipate the store. problem???
  ITERATOR->deliver(0, &x);
}
inline void if_pZone_instance::_sEvaluatingTotalSpots_2d_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}


void if_pZone_instance::_VerifyIsaCarOut_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    case if_sLoopInductive_Zone_signal:
      _VerifyIsaCarOut_1_fire(message);
      ITERATOR->restore();
      break;
    }
  _top_dispatch(message);
}

void if_pZone_instance::_VerifyIsaCarOut_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  
  
  if (! ITERATOR->guard(constraints,DELAYABLE))
    return; 
  if (!constraints[0].isEmpty() || DELAYABLE!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "244"); 
  _VerifyIsaCarOut_1a_fire(X);
    _VerifyIsaCarOut_1b_fire();
    _VerifyIsaCarOut_1c_fire();

  
  _VerifyIsaCarOut_1d_fire();
  
}
inline void if_pZone_instance::_VerifyIsaCarOut_1a_fire(IfMessage* X) {

  if_sLoopInductive_Zone_message* x = (if_sLoopInductive_Zone_message*) X;
  if_pid_copy(m_var.SENDER,x->m_par.p1);
  ITERATOR->trace(IfEvent::INPUT, m_pid, x->string(), m_pid, x->store());
}
inline void if_pZone_instance::_VerifyIsaCarOut_1b_fire() {

  if_i_spots_copy(m_var.TmpfreeSpots,m_var.infoTableZone.freeSpots);
}
inline void if_pZone_instance::_VerifyIsaCarOut_1c_fire() {

  if_i_spots_copy(m_var.TmptotalSpots,m_var.infoTableZone.totalSpots);
}
inline void if_pZone_instance::_VerifyIsaCarOut_1d_fire() {

  m_ctl.top=-1;
  m_ctl.top=8;
  
  nextstate();
}


if_state<16,if_pZone_instance::dispatcher> if_pZone_instance::STATE[] = {
  {"top", 0, 1, 0 | CONTROL,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_top_dispatch},
  {"RTDS_START", 0, 1, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_RTDS_START_dispatch},
  {"sWait", 0, 2, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_sWait_dispatch},
  {"Idle", 0, 3, 0 | TSIG,
    {0,0,0,0,1,1,1,0,1,0,1,0,0,0,1},
    &if_pZone_instance::_Idle_dispatch},
  {"WaitSensorIR4", 0, 4, 0 | TSIG,
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    &if_pZone_instance::_WaitSensorIR4_dispatch},
  {"WaitSensorIR2", 0, 5, 0 | TSIG,
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    &if_pZone_instance::_WaitSensorIR2_dispatch},
  {"sEvaluatingFreeSpots", 0, 6, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_sEvaluatingFreeSpots_dispatch},
  {"VerifyIsaCarEntering", 0, 7, 0 | TSIG,
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    &if_pZone_instance::_VerifyIsaCarEntering_dispatch},
  {"sEvaluatingTotalSpots", 0, 8, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_sEvaluatingTotalSpots_dispatch},
  {"VerifyIsaCarOut", 0, 9, 0 | TSIG,
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    &if_pZone_instance::_VerifyIsaCarOut_dispatch},
};





/* 
 * RTDS_start_process instance implementation 
 *
 */








inline void if_RTDS_start_process_ctl_copy
    (if_RTDS_start_process_ctl_type& x, const if_RTDS_start_process_ctl_type y) {
  if_integer_copy(x.top,y.top);
}
inline int if_RTDS_start_process_ctl_compare
    (const if_RTDS_start_process_ctl_type x, const if_RTDS_start_process_ctl_type y) {
  int c = 0;
  if (c == 0) c = if_integer_compare(x.top,y.top);
  return c;
}
inline void if_RTDS_start_process_ctl_print
    (const if_RTDS_start_process_ctl_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"top="); if_integer_print(x.top,f);
  fprintf(f,"}");
}
inline void if_RTDS_start_process_ctl_print_xml
    (const if_RTDS_start_process_ctl_type x, std::ostream& b) { 
  b << "<RTDS_start_process_ctl>\n";
  b << "<top>"; if_integer_print_xml(x.top,b); b << "</top>"; 
  b << "</RTDS_start_process_ctl>\n";
}
inline void if_RTDS_start_process_ctl_reset
    (if_RTDS_start_process_ctl_type& x) {
  if_integer_reset(x.top);
}

inline if_RTDS_start_process_ctl_type if_RTDS_start_process_ctl_make
    (if_integer_type top) {
  if_RTDS_start_process_ctl_type m_par;
  if_integer_copy(m_par.top,top);
  return m_par;
}

const char* if_RTDS_start_process_instance::NAME = IfInstance::PROCNAME[11] = "RTDS_start_process";



if_RTDS_start_process_instance::if_RTDS_start_process_instance() 
  : if_ParkingSystem_instance(if_pid_mk(if_RTDS_start_process_process,0), IfQueue::NIL) {
  m_ctl.top=-1;
  m_ctl.top=1;
  
    STATUS |=  CREATE;
  if_RTDS_start_process_var_reset(m_var);
  if_RTDS_start_process_par_reset(m_par);
    STATUS &= ~CREATE;
  
  
}

if_RTDS_start_process_instance::if_RTDS_start_process_instance(const if_RTDS_start_process_instance& instance) 
  : if_ParkingSystem_instance(instance) {
  if_RTDS_start_process_ctl_copy(m_ctl,instance.m_ctl);
  if_RTDS_start_process_var_copy(m_var,instance.m_var);
  if_RTDS_start_process_par_copy(m_par,instance.m_par);
}

const char* if_RTDS_start_process_instance::getState() const {
  static char r[1024];
  char tmp[256];
  *r = (char)0;
  if(m_ctl.top != -1) { sprintf(tmp,"top:%s,", STATE[m_ctl.top].name); strcat(r,tmp); }
  
  r[strlen(r)-1]=(char)0;
  return r;
}

int if_RTDS_start_process_instance::is(const unsigned flag) const {
  int ok = 0;
  if (m_ctl.top != -1)
    ok |= (STATE[m_ctl.top].flags & flag);
  return ok;
}

int if_RTDS_start_process_instance::compare(const IfInstance* X) const {
  if_RTDS_start_process_instance* x = (if_RTDS_start_process_instance*)X;
  int cmp = IfInstance::compare(X);
  if (cmp == 0) cmp = if_RTDS_start_process_ctl_compare(m_ctl,x->m_ctl);
  if (cmp == 0) cmp = if_RTDS_start_process_var_compare(m_var,x->m_var);
  if (cmp == 0) cmp = if_RTDS_start_process_par_compare(m_par,x->m_par);
  return cmp;
}

unsigned long if_RTDS_start_process_instance::hash(const unsigned long base) const {
  unsigned long key = m_pid;
  key += (unsigned long) m_queue; 
  if (sizeof(m_var) >= 4) // void 
    key += if_hash((char*) &m_var, sizeof(m_var), base);
  if (sizeof(m_par) >= 4) // void
    key += if_hash((char*) &m_par, sizeof(m_par), base);
  key += if_hash((char*) &m_ctl, sizeof(m_ctl), base);
  return key % base;
}

IfInstance* if_RTDS_start_process_instance::copy() const {
  return new if_RTDS_start_process_instance(*this);
}

void if_RTDS_start_process_instance::print(FILE* f) const {
  // warning: print the topmost state name only
  IfInstance::print(f);
  fprintf(f, "\n  @%s\t\t", getState());
  if_RTDS_start_process_var_print(m_var,f);
  fprintf(f, " ");
  if_RTDS_start_process_par_print(m_par,f);
}

void if_RTDS_start_process_instance::printXML(std::ostream& buf) const {
  buf << "<IfInstance ";
  buf << "type=\"RTDS_start_process\" ";
  buf << "state=\"" << getState() << "\" >\n";    
  IfInstance::printXML(buf);

  buf << "<var>\n";     
  if_RTDS_start_process_var_print_xml(m_var,buf);
  buf << "</var>\n";        

  buf << "<par>\n";     
  if_RTDS_start_process_par_print_xml(m_par,buf);
  buf << "</par>\n";        
  buf << "</IfInstance>\n";   
}

void if_RTDS_start_process_instance::copy(const IfInstance* X) {
  if_RTDS_start_process_instance* x = (if_RTDS_start_process_instance*) X;
  IfInstance::copy(X);
  if_RTDS_start_process_ctl_copy(m_ctl,x->m_ctl);
  if_RTDS_start_process_var_copy(m_var,x->m_var);
  if_RTDS_start_process_par_copy(m_par,x->m_par);
}

void if_RTDS_start_process_instance::reset() {
  if_RTDS_start_process_ctl_reset(m_ctl);
  m_ctl.top=-1;
  m_ctl.top=1;
  
  if_RTDS_start_process_var_reset(m_var);
  if_RTDS_start_process_par_reset(m_par);
}

void if_RTDS_start_process_instance::iterate(IfIterator* iterator) {
  STEP = 0;
  ITERATOR = iterator;
  fire();
  ITERATOR = NULL;
}


void if_RTDS_start_process_instance::fire() {
  unsigned step = STEP;

// CS: no DISCARD since it complicates everything
//  if (opt_discard && (STATE[m_sp].flags & STABLE)) {
//    IfMessage* message = NULL;
//    for(IfQueue* queue = m_queue; 
//        queue != IfQueue::NIL; 
//        queue = (IfQueue*) queue->getTail()) {
//      message = (IfMessage*) queue->getHead();
//      if (!save(message->getSid()))
//        break;
//      message = NULL;
//    }
//    if (message != NULL) {
//      m_queue = m_queue->remove(message);
//      if (STATE[m_sp].flags & TSIG) {
//        ITERATOR->record();
//        (this->*(STATE[m_sp].dispatch))(message);
//        ITERATOR->forget();
//      }
//      if(STEP == step) {
//        IfTime::Constraint constraints[] = {{0,0,0}};
//        ITERATOR->guard(constraints,EAGER);      
//        ITERATOR->trace(IfEvent::DISCARD, m_pid, message->string(), m_pid, message->store());
//        nextstate(-1);
//      }
//    }
//    ITERATOR->restore();
//  } else {

  int unstable = is(UNSTABLE);

  if ( is(TSIG) ) {
    IfMessage* message = NULL;
    for(IfQueue* queue = m_queue; 
        queue != IfQueue::NIL; 
        queue = (IfQueue*) queue->getTail()) {
      message = (IfMessage*) queue->getHead();
      if (!save(message->getSid()))
        break;
      message = NULL;
    }
    if (message != NULL) {
      m_queue = m_queue->remove(message);
      ITERATOR->record();
      dispatch(message, unstable);
      ITERATOR->forget();
    }
    ITERATOR->restore();
  }
//  }
  if ( is(TNONE) )
    dispatch(NULL, unstable);
  if ( is(TSIG) ) {
    
  }

  if (is(UNSTABLE) && step == STEP)
      fprintf(stderr, "\nerror #2: unstable deadlock: %s@%s\n", 
          NAME, getState());
}

void if_RTDS_start_process_instance::dispatch(IfMessage* message, int unstable) {
  if (m_ctl.top != -1 && (int)(STATE[m_ctl.top].flags & UNSTABLE) == unstable)
    (this->*(STATE[m_ctl.top].dispatch))(message);
  
}

void if_RTDS_start_process_instance::nextstate() {

  if ( !is(UNSTABLE) )
    ITERATOR->step();
  else {
    ITERATOR->record();
    fire();
    ITERATOR->forget();
  }
}



void if_RTDS_start_process_instance::_top_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  
}

void if_RTDS_start_process_instance::_RTDS_START_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _RTDS_START_1_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_RTDS_start_process_instance::_RTDS_START_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_boolean_true))
    return;
  
  if (! ITERATOR->guard(constraints,EAGER))
    return; 
  if (!constraints[0].isEmpty() || EAGER!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "254"); 
  
    _RTDS_START_1a_fire();
    _RTDS_START_1b_fire();

  
  _RTDS_START_1c_fire();
  
}
inline void if_RTDS_start_process_instance::_RTDS_START_1a_fire() {

  if_pid_type y;
  if_pZone_instance x(if_pid_nil);
  ITERATOR->fork(&x, &y);
  ITERATOR->trace(IfEvent::FORK, m_pid, "pZone", y);
}
inline void if_RTDS_start_process_instance::_RTDS_START_1b_fire() {

  unsigned pid = m_pid;
  ITERATOR->trace(IfEvent::KILL, m_pid, "", pid);
  if (m_pid != pid)
    ITERATOR->kill(pid);
}
inline void if_RTDS_start_process_instance::_RTDS_START_1c_fire() {

  ITERATOR->kill(m_pid);
  ITERATOR->step();
}


if_state<16,if_RTDS_start_process_instance::dispatcher> if_RTDS_start_process_instance::STATE[] = {
  {"top", 0, 1, 0 | CONTROL,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_RTDS_start_process_instance::_top_dispatch},
  {"RTDS_START", 0, 1, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_RTDS_start_process_instance::_RTDS_START_dispatch},
};






/* 
 * obsInitPid instance implementation 
 *
 */


inline void if_obsInitPid_var_copy
    (if_obsInitPid_var_type& x, const if_obsInitPid_var_type y) {
  if_pid_copy(x.pidSender,y.pidSender);
  if_pid_copy(x.pidCtrl,y.pidCtrl);
  if_pid_copy(x.pidZone,y.pidZone);
  if_integer_copy(x.tmpVar,y.tmpVar);
}
inline int if_obsInitPid_var_compare
    (const if_obsInitPid_var_type x, const if_obsInitPid_var_type y) {
  int c = 0;
  if (c == 0) c = if_pid_compare(x.pidSender,y.pidSender);
  if (c == 0) c = if_pid_compare(x.pidCtrl,y.pidCtrl);
  if (c == 0) c = if_pid_compare(x.pidZone,y.pidZone);
  if (c == 0) c = if_integer_compare(x.tmpVar,y.tmpVar);
  return c;
}
inline void if_obsInitPid_var_print
    (const if_obsInitPid_var_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"pidSender="); if_pid_print(x.pidSender,f); fprintf(f,",");
  fprintf(f,"pidCtrl="); if_pid_print(x.pidCtrl,f); fprintf(f,",");
  fprintf(f,"pidZone="); if_pid_print(x.pidZone,f); fprintf(f,",");
  fprintf(f,"tmpVar="); if_integer_print(x.tmpVar,f);
  fprintf(f,"}");
}
inline void if_obsInitPid_var_print_xml
    (const if_obsInitPid_var_type x, std::ostream& b) { 
  b << "<obsInitPid_var>\n";
  b << "<pidSender>"; if_pid_print_xml(x.pidSender,b); b << "</pidSender>";
  b << "<pidCtrl>"; if_pid_print_xml(x.pidCtrl,b); b << "</pidCtrl>";
  b << "<pidZone>"; if_pid_print_xml(x.pidZone,b); b << "</pidZone>";
  b << "<tmpVar>"; if_integer_print_xml(x.tmpVar,b); b << "</tmpVar>"; 
  b << "</obsInitPid_var>\n";
}
inline void if_obsInitPid_var_reset
    (if_obsInitPid_var_type& x) {
  if_pid_reset(x.pidSender);
  if_pid_reset(x.pidCtrl);
  if_pid_reset(x.pidZone);
  if_integer_reset(x.tmpVar);
}

inline if_obsInitPid_var_type if_obsInitPid_var_make
    (if_pid_type pidSender,if_pid_type pidCtrl,if_pid_type pidZone,if_integer_type tmpVar) {
  if_obsInitPid_var_type m_par;
  if_pid_copy(m_par.pidSender,pidSender);
  if_pid_copy(m_par.pidCtrl,pidCtrl);
  if_pid_copy(m_par.pidZone,pidZone);
  if_integer_copy(m_par.tmpVar,tmpVar);
  return m_par;
}


inline void if_obsInitPid_ctl_copy
    (if_obsInitPid_ctl_type& x, const if_obsInitPid_ctl_type y) {
  if_integer_copy(x.top,y.top);
}
inline int if_obsInitPid_ctl_compare
    (const if_obsInitPid_ctl_type x, const if_obsInitPid_ctl_type y) {
  int c = 0;
  if (c == 0) c = if_integer_compare(x.top,y.top);
  return c;
}
inline void if_obsInitPid_ctl_print
    (const if_obsInitPid_ctl_type x, FILE* f) { 
  fprintf(f,"{");
  fprintf(f,"top="); if_integer_print(x.top,f);
  fprintf(f,"}");
}
inline void if_obsInitPid_ctl_print_xml
    (const if_obsInitPid_ctl_type x, std::ostream& b) { 
  b << "<obsInitPid_ctl>\n";
  b << "<top>"; if_integer_print_xml(x.top,b); b << "</top>"; 
  b << "</obsInitPid_ctl>\n";
}
inline void if_obsInitPid_ctl_reset
    (if_obsInitPid_ctl_type& x) {
  if_integer_reset(x.top);
}

inline if_obsInitPid_ctl_type if_obsInitPid_ctl_make
    (if_integer_type top) {
  if_obsInitPid_ctl_type m_par;
  if_integer_copy(m_par.top,top);
  return m_par;
}

const char* if_obsInitPid_instance::NAME = IfInstance::PROCNAME[12] = "obsInitPid";



if_obsInitPid_instance::if_obsInitPid_instance() 
  : IfObserverInstance(if_pid_mk(if_obsInitPid_observer,0), IfQueue::NIL) {
  m_ctl.top=-1;
  m_ctl.top=1;
  
    STATUS |=  CREATE;
  if_obsInitPid_var_reset(m_var);
    STATUS &= ~CREATE;
  if_integer_copy(m_var.tmpVar,0);
  
}

if_obsInitPid_instance::if_obsInitPid_instance(const if_obsInitPid_instance& instance) 
  : IfObserverInstance(instance) {
  if_obsInitPid_ctl_copy(m_ctl,instance.m_ctl);
  if_obsInitPid_var_copy(m_var,instance.m_var);
}

const char* if_obsInitPid_instance::getState() const {
  static char r[1024];
  char tmp[256];
  *r = (char)0;
  if(m_ctl.top != -1) { sprintf(tmp,"top:%s,", STATE[m_ctl.top].name); strcat(r,tmp); }
  
  r[strlen(r)-1]=(char)0;
  return r;
}

int if_obsInitPid_instance::is(const unsigned flag) const {
  int ok = 0;
  if (m_ctl.top != -1)
    ok |= (STATE[m_ctl.top].flags & flag);
  return ok;
}

int if_obsInitPid_instance::compare(const IfInstance* X) const {
  if_obsInitPid_instance* x = (if_obsInitPid_instance*)X;
  int cmp = IfObserverInstance::compare(X);
  if (cmp == 0) cmp = if_obsInitPid_ctl_compare(m_ctl,x->m_ctl);
  if (cmp == 0) cmp = if_obsInitPid_var_compare(m_var,x->m_var);
  return cmp;
}

unsigned long if_obsInitPid_instance::hash(const unsigned long base) const {
  unsigned long key = m_pid;
  key += (unsigned long) m_curLabel; 
  if (sizeof(m_var) >= 4) // void 
    key += if_hash((char*) &m_var, sizeof(m_var), base);
  key += if_hash((char*) &m_ctl, sizeof(m_ctl), base);
  return key % base;
}

IfInstance* if_obsInitPid_instance::copy() const {
  return new if_obsInitPid_instance(*this);
}

void if_obsInitPid_instance::print(FILE* f) const {
  // warning: print the topmost state name only
  IfObserverInstance::print(f);
  fprintf(f, "\n  @%s\t\t", getState());
  if_obsInitPid_var_print(m_var,f);
}

void if_obsInitPid_instance::printXML(std::ostream& buf) const {
  buf << "<IfObserverInstance ";
  buf << "type=\"obsInitPid\" ";
  buf << "state=\"" << getState() << "\" ";
  buf << "status = \"" << (isObsError()? "error" : (isObsSuccess()? "success" : "none")) << "\" ";
  buf << "cut=\"" << (m_bCut?"true":"false") << "\" >\n";    

  IfObserverInstance::printXML(buf);

  buf << "<var>\n";     
  if_obsInitPid_var_print_xml(m_var,buf);
  buf << "</var>\n";        

  buf << "</IfObserverInstance>\n";
}

void if_obsInitPid_instance::copy(const IfInstance* X) {
  if_obsInitPid_instance* x = (if_obsInitPid_instance*) X;
  IfObserverInstance::copy(X);
  if_obsInitPid_ctl_copy(m_ctl,x->m_ctl);
  if_obsInitPid_var_copy(m_var,x->m_var);
}

void if_obsInitPid_instance::reset() {
  if_obsInitPid_ctl_reset(m_ctl);
  m_ctl.top=-1;
  m_ctl.top=1;
  
  if_obsInitPid_var_reset(m_var);
}

void if_obsInitPid_instance::iterate(IfIterator* iter) {
  STEP = 0;
  ITERATOR = iter;
  fire();
  ITERATOR = NULL;
}

void if_obsInitPid_instance::fire() {
  unsigned step = STEP;

  int unstable = is(UNSTABLE);

  if ( is(TSIG) ) {
    IfMessage* message = NULL;
    for(IfQueue* queue = m_queue; 
        queue != IfQueue::NIL; 
        queue = (IfQueue*) queue->getTail()) {
      message = (IfMessage*) queue->getHead();
      if (!save(message->getSid()))
        break;
      message = NULL;
    }
    if (message != NULL) {
      m_queue = m_queue->remove(message);
      ITERATOR->record();
      dispatch(message, unstable);
      ITERATOR->forget();
    }
    ITERATOR->restore();
  }
  if ( is(TNONE) )
    dispatch(NULL, unstable);
  if ( is(TSIG) ) {
    
  }

  if (is(UNSTABLE) && step == STEP)
      fprintf(stderr, "\nerror #2: unstable deadlock: %s@%s\n", 
          NAME, STATE[m_ctl.top].name);
}

void if_obsInitPid_instance::dispatch(IfMessage* message, int unstable) {
  if (m_ctl.top != -1 && (int)(STATE[m_ctl.top].flags & UNSTABLE) == unstable)
    (this->*(STATE[m_ctl.top].dispatch))(message);
  
}

void if_obsInitPid_instance::nextstate() {

  if ( !is(UNSTABLE) )
    ITERATOR->step();
  else {
    ITERATOR->record();
    fire();
    ITERATOR->forget();
  }
}



void if_obsInitPid_instance::_top_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  
}

void if_obsInitPid_instance::_RTDS_START_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _RTDS_START_1_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_obsInitPid_instance::_RTDS_START_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_boolean_true))
    return;
  
  if (! ITERATOR->guard(constraints,LAZY))
    return; 
  if (!constraints[0].isEmpty() || LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "272"); 
  

  
  _RTDS_START_1a_fire();
  
}

inline void if_obsInitPid_instance::_RTDS_START_1a_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}


void if_obsInitPid_instance::_sOk_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _sOk_1_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_obsInitPid_instance::_sOk_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_boolean_true))
    return;
  
  if (! ITERATOR->guard(constraints,LAZY))
    return; 
  if (!constraints[0].isEmpty() || LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "278"); 
  
    _sOk_1a_fire();

  
  _sOk_1b_fire();
  
}
inline void if_obsInitPid_instance::_sOk_1a_fire() {

  IfObserverInstance::cut();
}
inline void if_obsInitPid_instance::_sOk_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=6;
  
  nextstate();
}


void if_obsInitPid_instance::_Idle_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _Idle_1_fire(message);
      ITERATOR->restore();
      _Idle_2_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_obsInitPid_instance::_Idle_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (((if_obs_output(if_sTemp_signal, 0, (unsigned)-1, (unsigned)-1, (unsigned)-1))!= NULL && (if_sTemp_signal == (if_obs_output(if_sTemp_signal, 0, (unsigned)-1, (unsigned)-1, (unsigned)-1))->getSid()))))
    return;
  
  if (! ITERATOR->guard(constraints,LAZY))
    return; 
  if (!constraints[0].isEmpty() || LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "286"); 
  _Idle_1a_fire(X);

  
  _Idle_1b_fire();
  
}
inline void if_obsInitPid_instance::_Idle_1a_fire(IfMessage* X) {

  if_sTemp_message* x = (if_sTemp_message*)if_obs_output_ext(if_sTemp_signal, 0, &m_var.pidZone, NULL, NULL) ;
  if_pid_copy(m_var.pidSender,x->m_par.p1);
}

inline void if_obsInitPid_instance::_Idle_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=4;
  
  nextstate();
}

void if_obsInitPid_instance::_Idle_2_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (((if_obs_input(if_sInitPidCtrl_signal, (unsigned)-1))!= NULL && (if_sInitPidCtrl_signal == (if_obs_input(if_sInitPidCtrl_signal, (unsigned)-1))->getSid()))))
    return;
  
  if (! ITERATOR->guard(constraints,LAZY))
    return; 
  if (!constraints[0].isEmpty() || LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "288"); 
  _Idle_2a_fire(X);
    _Idle_2b_fire();

  
  _Idle_2c_fire();
  
}
inline void if_obsInitPid_instance::_Idle_2a_fire(IfMessage* X) {

  if_sInitPidCtrl_message* x = (if_sInitPidCtrl_message*)if_obs_input_ext(if_sInitPidCtrl_signal, &m_var.pidZone) ;
  if_pid_copy(m_var.pidSender,x->m_par.p1);
  if_pid_copy(m_var.pidCtrl,x->m_par.p2);

}
inline void if_obsInitPid_instance::_Idle_2b_fire() {

  if_integer_copy(m_var.tmpVar,1);
}
inline void if_obsInitPid_instance::_Idle_2c_fire() {

  m_ctl.top=-1;
  m_ctl.top=3;
  
  nextstate();
}


void if_obsInitPid_instance::_RTDS_decision_SYMB10_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _RTDS_decision_SYMB10_1_fire(message);
      ITERATOR->restore();
      _RTDS_decision_SYMB10_2_fire(message);
      ITERATOR->restore();
      
    }
  
}

void if_obsInitPid_instance::_RTDS_decision_SYMB10_1_fire(IfMessage* X) {
  
  if (! (if_boolean_not(if_integer_eq(m_var.tmpVar,1))))
    return;
  
   
  if (LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "295"); 
  

  
  _RTDS_decision_SYMB10_1a_fire();
  
}

inline void if_obsInitPid_instance::_RTDS_decision_SYMB10_1a_fire() {

  m_ctl.top=-1;
  m_ctl.top=5;
  
  nextstate();
}

void if_obsInitPid_instance::_RTDS_decision_SYMB10_2_fire(IfMessage* X) {
  
  if (! (if_integer_eq(m_var.tmpVar,1)))
    return;
  
   
  if (LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "298"); 
  
    _RTDS_decision_SYMB10_2a_fire();

  
  _RTDS_decision_SYMB10_2b_fire();
  
}
inline void if_obsInitPid_instance::_RTDS_decision_SYMB10_2a_fire() {

  if_integer_copy(m_var.tmpVar,0);
}
inline void if_obsInitPid_instance::_RTDS_decision_SYMB10_2b_fire() {

  m_ctl.top=-1;
  m_ctl.top=2;
  
  nextstate();
}


void if_obsInitPid_instance::_sError_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  else {
    _sError_1_fire(message);
      ITERATOR->restore();
      
    }
  _top_dispatch(message);
}

void if_obsInitPid_instance::_sError_1_fire(IfMessage* X) {
  IfTime::Constraint constraints[] = 
    {{0,0,0}};
  if (! (if_boolean_true))
    return;
  
  if (! ITERATOR->guard(constraints,LAZY))
    return; 
  if (!constraints[0].isEmpty() || LAZY!=EAGER) 
    if(getPriority() != OBSERVER_PRIORITY) ITERATOR->trace(IfEvent::DELTA, m_pid, "");
  
  if (opt_gen_lineno) ITERATOR->trace(IfEvent::DEBUG, m_pid, "305"); 
  
    _sError_1a_fire();

  
  _sError_1b_fire();
  
}
inline void if_obsInitPid_instance::_sError_1a_fire() {

  IfObserverInstance::cut();
}
inline void if_obsInitPid_instance::_sError_1b_fire() {

  m_ctl.top=-1;
  m_ctl.top=6;
  
  nextstate();
}


void if_obsInitPid_instance::_DEAD_dispatch(IfMessage* message) {
  if (message != NULL)
    switch(message->getSid()) {
    }
  _top_dispatch(message);
}

if_state<16,if_obsInitPid_instance::dispatcher> if_obsInitPid_instance::STATE[] = {
  {"top", 0, 1, 0 | CONTROL,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_top_dispatch},
  {"RTDS_START", 0, 1, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_RTDS_START_dispatch},
  {"sOk", 0, 2, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_sOk_dispatch},
  {"Idle", 0, 3, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_Idle_dispatch},
  {"RTDS_decision_SYMB10", 0, 4, 0 | UNSTABLE | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_RTDS_decision_SYMB10_dispatch},
  {"sError", 0, 5, 0 | TNONE | OERROR,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_sError_dispatch},
  {"DEAD", 0, 6, 0,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_DEAD_dispatch},
};





IfConfig* IfIterator::start() {
  if_pid_type pid = 0;
  IfInstance* instance = NULL;
  IfConfig empty(1);
  
  m_config.put(&empty);

  
  instance = new if_RTDS_start_process_instance;
  fork(instance, &pid);
  delete instance;
  instance = new if_obsInitPid_instance;
  fork(instance, &pid);
  delete instance;
  

  

  instance = new IfDiscreteTime();
  fork(instance, &pid);
  delete instance; 

  // options
  opt_use_priorities = 1;

  return m_config.get();
}

IfPriorityFilter::Rule* IfPriorityFilter::RULE = new IfPriorityFilter::Rule[1];

IfPriorityFilter::Rule P0 = IfPriorityFilter::RULE[0] = NULL;
