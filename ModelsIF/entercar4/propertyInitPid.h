


/*
 *
 * IF-2.0 Intermediate Representation.
 * 
 * Copyright (C) Verimag Grenoble.
 *
 * Marius Bozga
 *
 */









typedef if_integer_type if_RTDS_character_type;

#define if_RTDS_character_copy(x,y) if_integer_copy(x,y)
#define if_RTDS_character_compare(x,y) if_integer_compare(x,y)
#define if_RTDS_character_print(x,f) if_integer_print(x,f)
#define if_RTDS_character_print_xml(x,b) if_integer_print_xml(x,b)
#define if_RTDS_character_reset(x) (x)=32
#define if_RTDS_character_iterate(x) for(x=32;x<=127;x++)
#define if_RTDS_character_eq(x,y) if_RTDS_character_compare(x,y)==0
#define if_RTDS_character_ne(x,y) if_RTDS_character_compare(x,y)!=0

struct if_RTDS_charstring_type {
  int length;
  if_RTDS_character_type elem[128];

  if_RTDS_character_type& operator[](const int i) 
    { return elem[i]; }
};

inline void if_RTDS_charstring_copy
    (if_RTDS_charstring_type& x, const if_RTDS_charstring_type y);
inline int if_RTDS_charstring_compare
    (const if_RTDS_charstring_type x, const if_RTDS_charstring_type y);
inline void if_RTDS_charstring_print
    (const if_RTDS_charstring_type x, FILE* f);
inline void if_RTDS_charstring_reset
    (if_RTDS_charstring_type& x);
inline int if_RTDS_charstring_length
    (const if_RTDS_charstring_type x);
if_RTDS_charstring_type if_RTDS_charstring_make
    ();
if_RTDS_charstring_type if_RTDS_charstring_make
    (const if_RTDS_character_type e);
if_RTDS_charstring_type if_RTDS_charstring_concat
    (const if_RTDS_charstring_type x, const if_RTDS_charstring_type y);
if_RTDS_charstring_type if_RTDS_charstring_substring
    (const if_RTDS_charstring_type x, const int k, const int l);
if_RTDS_charstring_type if_RTDS_charstring_remove
    (const if_RTDS_charstring_type x, const int k);
if_RTDS_charstring_type if_RTDS_charstring_insert
    (const if_RTDS_charstring_type x, const int k, const if_RTDS_character_type e);
int if_RTDS_charstring_index
    (const if_RTDS_charstring_type x, const if_RTDS_character_type e);
#define if_RTDS_charstring_eq(x,y) if_RTDS_charstring_compare(x,y)==0
#define if_RTDS_charstring_ne(x,y) if_RTDS_charstring_compare(x,y)!=0

typedef if_integer_type if_i_spots_type;

#define if_i_spots_copy(x,y) if_integer_copy(x,y)
#define if_i_spots_compare(x,y) if_integer_compare(x,y)
#define if_i_spots_print(x,f) if_integer_print(x,f)
#define if_i_spots_print_xml(x,b) if_integer_print_xml(x,b)
#define if_i_spots_reset(x) (x)=0
#define if_i_spots_iterate(x) for(x=0;x<=2;x++)
#define if_i_spots_eq(x,y) if_i_spots_compare(x,y)==0
#define if_i_spots_ne(x,y) if_i_spots_compare(x,y)!=0

typedef struct {
  if_i_spots_type totalSpots;
  if_i_spots_type freeSpots;
  if_pid_type ID;
} if_InfoZone_type;

inline void if_InfoZone_copy
    (if_InfoZone_type& x, const if_InfoZone_type y);
inline int if_InfoZone_compare
    (const if_InfoZone_type x, const if_InfoZone_type y);
inline void if_InfoZone_print
    (const if_InfoZone_type x, FILE* f);
inline void if_InfoZone_reset
    (if_InfoZone_type& x);
#define if_InfoZone_iterate(x)\
  if_i_spots_iterate(x.totalSpots)\
  if_i_spots_iterate(x.freeSpots)\
  if_pid_iterate(x.ID)
inline if_InfoZone_type if_InfoZone_make
    (if_i_spots_type totalSpots,if_i_spots_type freeSpots,if_pid_type ID);
#define if_InfoZone_eq(x,y) if_InfoZone_compare(x,y)==0
#define if_InfoZone_ne(x,y) if_InfoZone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_t_sEntered_Car_type;

inline void if_t_sEntered_Car_copy
    (if_t_sEntered_Car_type& x, const if_t_sEntered_Car_type y);
inline int if_t_sEntered_Car_compare
    (const if_t_sEntered_Car_type x, const if_t_sEntered_Car_type y);
inline void if_t_sEntered_Car_print
    (const if_t_sEntered_Car_type x, FILE* f);
inline void if_t_sEntered_Car_reset
    (if_t_sEntered_Car_type& x);
#define if_t_sEntered_Car_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_t_sEntered_Car_type if_t_sEntered_Car_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_t_sEntered_Car_eq(x,y) if_t_sEntered_Car_compare(x,y)==0
#define if_t_sEntered_Car_ne(x,y) if_t_sEntered_Car_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_t_sOut_Car_type;

inline void if_t_sOut_Car_copy
    (if_t_sOut_Car_type& x, const if_t_sOut_Car_type y);
inline int if_t_sOut_Car_compare
    (const if_t_sOut_Car_type x, const if_t_sOut_Car_type y);
inline void if_t_sOut_Car_print
    (const if_t_sOut_Car_type x, FILE* f);
inline void if_t_sOut_Car_reset
    (if_t_sOut_Car_type& x);
#define if_t_sOut_Car_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_t_sOut_Car_type if_t_sOut_Car_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_t_sOut_Car_eq(x,y) if_t_sOut_Car_compare(x,y)==0
#define if_t_sOut_Car_ne(x,y) if_t_sOut_Car_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_t_sOkInit_type;

inline void if_t_sOkInit_copy
    (if_t_sOkInit_type& x, const if_t_sOkInit_type y);
inline int if_t_sOkInit_compare
    (const if_t_sOkInit_type x, const if_t_sOkInit_type y);
inline void if_t_sOkInit_print
    (const if_t_sOkInit_type x, FILE* f);
inline void if_t_sOkInit_reset
    (if_t_sOkInit_type& x);
#define if_t_sOkInit_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_t_sOkInit_type if_t_sOkInit_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_t_sOkInit_eq(x,y) if_t_sOkInit_compare(x,y)==0
#define if_t_sOkInit_ne(x,y) if_t_sOkInit_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_t_sInfoZone_type;

inline void if_t_sInfoZone_copy
    (if_t_sInfoZone_type& x, const if_t_sInfoZone_type y);
inline int if_t_sInfoZone_compare
    (const if_t_sInfoZone_type x, const if_t_sInfoZone_type y);
inline void if_t_sInfoZone_print
    (const if_t_sInfoZone_type x, FILE* f);
inline void if_t_sInfoZone_reset
    (if_t_sInfoZone_type& x);
#define if_t_sInfoZone_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_t_sInfoZone_type if_t_sInfoZone_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_t_sInfoZone_eq(x,y) if_t_sInfoZone_compare(x,y)==0
#define if_t_sInfoZone_ne(x,y) if_t_sInfoZone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_i_spots_type p2;
} if_t_sInitFreeSpot_type;

inline void if_t_sInitFreeSpot_copy
    (if_t_sInitFreeSpot_type& x, const if_t_sInitFreeSpot_type y);
inline int if_t_sInitFreeSpot_compare
    (const if_t_sInitFreeSpot_type x, const if_t_sInitFreeSpot_type y);
inline void if_t_sInitFreeSpot_print
    (const if_t_sInitFreeSpot_type x, FILE* f);
inline void if_t_sInitFreeSpot_reset
    (if_t_sInitFreeSpot_type& x);
#define if_t_sInitFreeSpot_iterate(x)\
  if_pid_iterate(x.p1)\
  if_i_spots_iterate(x.p2)
inline if_t_sInitFreeSpot_type if_t_sInitFreeSpot_make
    (if_pid_type p1,if_i_spots_type p2);
#define if_t_sInitFreeSpot_eq(x,y) if_t_sInitFreeSpot_compare(x,y)==0
#define if_t_sInitFreeSpot_ne(x,y) if_t_sInitFreeSpot_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_i_spots_type p2;
} if_t_sInitTotalSpots_type;

inline void if_t_sInitTotalSpots_copy
    (if_t_sInitTotalSpots_type& x, const if_t_sInitTotalSpots_type y);
inline int if_t_sInitTotalSpots_compare
    (const if_t_sInitTotalSpots_type x, const if_t_sInitTotalSpots_type y);
inline void if_t_sInitTotalSpots_print
    (const if_t_sInitTotalSpots_type x, FILE* f);
inline void if_t_sInitTotalSpots_reset
    (if_t_sInitTotalSpots_type& x);
#define if_t_sInitTotalSpots_iterate(x)\
  if_pid_iterate(x.p1)\
  if_i_spots_iterate(x.p2)
inline if_t_sInitTotalSpots_type if_t_sInitTotalSpots_make
    (if_pid_type p1,if_i_spots_type p2);
#define if_t_sInitTotalSpots_eq(x,y) if_t_sInitTotalSpots_compare(x,y)==0
#define if_t_sInitTotalSpots_ne(x,y) if_t_sInitTotalSpots_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sReqInfo_type;

inline void if_t_sReqInfo_copy
    (if_t_sReqInfo_type& x, const if_t_sReqInfo_type y);
inline int if_t_sReqInfo_compare
    (const if_t_sReqInfo_type x, const if_t_sReqInfo_type y);
inline void if_t_sReqInfo_print
    (const if_t_sReqInfo_type x, FILE* f);
inline void if_t_sReqInfo_reset
    (if_t_sReqInfo_type& x);
#define if_t_sReqInfo_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sReqInfo_type if_t_sReqInfo_make
    (if_pid_type p1);
#define if_t_sReqInfo_eq(x,y) if_t_sReqInfo_compare(x,y)==0
#define if_t_sReqInfo_ne(x,y) if_t_sReqInfo_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sLoopInductive_Zone_type;

inline void if_t_sLoopInductive_Zone_copy
    (if_t_sLoopInductive_Zone_type& x, const if_t_sLoopInductive_Zone_type y);
inline int if_t_sLoopInductive_Zone_compare
    (const if_t_sLoopInductive_Zone_type x, const if_t_sLoopInductive_Zone_type y);
inline void if_t_sLoopInductive_Zone_print
    (const if_t_sLoopInductive_Zone_type x, FILE* f);
inline void if_t_sLoopInductive_Zone_reset
    (if_t_sLoopInductive_Zone_type& x);
#define if_t_sLoopInductive_Zone_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sLoopInductive_Zone_type if_t_sLoopInductive_Zone_make
    (if_pid_type p1);
#define if_t_sLoopInductive_Zone_eq(x,y) if_t_sLoopInductive_Zone_compare(x,y)==0
#define if_t_sLoopInductive_Zone_ne(x,y) if_t_sLoopInductive_Zone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sIR1_Zone_type;

inline void if_t_sIR1_Zone_copy
    (if_t_sIR1_Zone_type& x, const if_t_sIR1_Zone_type y);
inline int if_t_sIR1_Zone_compare
    (const if_t_sIR1_Zone_type x, const if_t_sIR1_Zone_type y);
inline void if_t_sIR1_Zone_print
    (const if_t_sIR1_Zone_type x, FILE* f);
inline void if_t_sIR1_Zone_reset
    (if_t_sIR1_Zone_type& x);
#define if_t_sIR1_Zone_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sIR1_Zone_type if_t_sIR1_Zone_make
    (if_pid_type p1);
#define if_t_sIR1_Zone_eq(x,y) if_t_sIR1_Zone_compare(x,y)==0
#define if_t_sIR1_Zone_ne(x,y) if_t_sIR1_Zone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sIR2_Zone_type;

inline void if_t_sIR2_Zone_copy
    (if_t_sIR2_Zone_type& x, const if_t_sIR2_Zone_type y);
inline int if_t_sIR2_Zone_compare
    (const if_t_sIR2_Zone_type x, const if_t_sIR2_Zone_type y);
inline void if_t_sIR2_Zone_print
    (const if_t_sIR2_Zone_type x, FILE* f);
inline void if_t_sIR2_Zone_reset
    (if_t_sIR2_Zone_type& x);
#define if_t_sIR2_Zone_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sIR2_Zone_type if_t_sIR2_Zone_make
    (if_pid_type p1);
#define if_t_sIR2_Zone_eq(x,y) if_t_sIR2_Zone_compare(x,y)==0
#define if_t_sIR2_Zone_ne(x,y) if_t_sIR2_Zone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sIR3_Zone_type;

inline void if_t_sIR3_Zone_copy
    (if_t_sIR3_Zone_type& x, const if_t_sIR3_Zone_type y);
inline int if_t_sIR3_Zone_compare
    (const if_t_sIR3_Zone_type x, const if_t_sIR3_Zone_type y);
inline void if_t_sIR3_Zone_print
    (const if_t_sIR3_Zone_type x, FILE* f);
inline void if_t_sIR3_Zone_reset
    (if_t_sIR3_Zone_type& x);
#define if_t_sIR3_Zone_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sIR3_Zone_type if_t_sIR3_Zone_make
    (if_pid_type p1);
#define if_t_sIR3_Zone_eq(x,y) if_t_sIR3_Zone_compare(x,y)==0
#define if_t_sIR3_Zone_ne(x,y) if_t_sIR3_Zone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sIR4_Zone_type;

inline void if_t_sIR4_Zone_copy
    (if_t_sIR4_Zone_type& x, const if_t_sIR4_Zone_type y);
inline int if_t_sIR4_Zone_compare
    (const if_t_sIR4_Zone_type x, const if_t_sIR4_Zone_type y);
inline void if_t_sIR4_Zone_print
    (const if_t_sIR4_Zone_type x, FILE* f);
inline void if_t_sIR4_Zone_reset
    (if_t_sIR4_Zone_type& x);
#define if_t_sIR4_Zone_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sIR4_Zone_type if_t_sIR4_Zone_make
    (if_pid_type p1);
#define if_t_sIR4_Zone_eq(x,y) if_t_sIR4_Zone_compare(x,y)==0
#define if_t_sIR4_Zone_ne(x,y) if_t_sIR4_Zone_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
} if_t_sOkInitPid_type;

inline void if_t_sOkInitPid_copy
    (if_t_sOkInitPid_type& x, const if_t_sOkInitPid_type y);
inline int if_t_sOkInitPid_compare
    (const if_t_sOkInitPid_type x, const if_t_sOkInitPid_type y);
inline void if_t_sOkInitPid_print
    (const if_t_sOkInitPid_type x, FILE* f);
inline void if_t_sOkInitPid_reset
    (if_t_sOkInitPid_type& x);
#define if_t_sOkInitPid_iterate(x)\
  if_pid_iterate(x.p1)
inline if_t_sOkInitPid_type if_t_sOkInitPid_make
    (if_pid_type p1);
#define if_t_sOkInitPid_eq(x,y) if_t_sOkInitPid_compare(x,y)==0
#define if_t_sOkInitPid_ne(x,y) if_t_sOkInitPid_compare(x,y)!=0

typedef struct {
  if_pid_type p1;
  if_pid_type p2;
} if_t_sInitPidCtrl_type;

inline void if_t_sInitPidCtrl_copy
    (if_t_sInitPidCtrl_type& x, const if_t_sInitPidCtrl_type y);
inline int if_t_sInitPidCtrl_compare
    (const if_t_sInitPidCtrl_type x, const if_t_sInitPidCtrl_type y);
inline void if_t_sInitPidCtrl_print
    (const if_t_sInitPidCtrl_type x, FILE* f);
inline void if_t_sInitPidCtrl_reset
    (if_t_sInitPidCtrl_type& x);
#define if_t_sInitPidCtrl_iterate(x)\
  if_pid_iterate(x.p1)\
  if_pid_iterate(x.p2)
inline if_t_sInitPidCtrl_type if_t_sInitPidCtrl_make
    (if_pid_type p1,if_pid_type p2);
#define if_t_sInitPidCtrl_eq(x,y) if_t_sInitPidCtrl_compare(x,y)==0
#define if_t_sInitPidCtrl_ne(x,y) if_t_sInitPidCtrl_compare(x,y)!=0

typedef IfMessage* if_t_if_signal_type;

#define if_t_if_signal_eq(x,y) if_t_if_signal_compare(x,y)==0
#define if_t_if_signal_ne(x,y) if_t_if_signal_compare(x,y)!=0


/* 
 * sEntered_Car message interface 
 *
 */

#define if_sEntered_Car_signal 0


typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_sEntered_Car_par_type;

inline void if_sEntered_Car_par_copy
    (if_sEntered_Car_par_type& x, const if_sEntered_Car_par_type y);
inline int if_sEntered_Car_par_compare
    (const if_sEntered_Car_par_type x, const if_sEntered_Car_par_type y);
inline void if_sEntered_Car_par_print
    (const if_sEntered_Car_par_type x, FILE* f);
inline void if_sEntered_Car_par_reset
    (if_sEntered_Car_par_type& x);
#define if_sEntered_Car_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_sEntered_Car_par_type if_sEntered_Car_par_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_sEntered_Car_par_eq(x,y) if_sEntered_Car_par_compare(x,y)==0
#define if_sEntered_Car_par_ne(x,y) if_sEntered_Car_par_compare(x,y)!=0

class if_sEntered_Car_message : public IfMessage {

public:
  if_sEntered_Car_message();
  if_sEntered_Car_message(if_pid_type p1,if_InfoZone_type p2);
  if_sEntered_Car_message(const if_sEntered_Car_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sEntered_Car_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sOut_Car message interface 
 *
 */

#define if_sOut_Car_signal 1


typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_sOut_Car_par_type;

inline void if_sOut_Car_par_copy
    (if_sOut_Car_par_type& x, const if_sOut_Car_par_type y);
inline int if_sOut_Car_par_compare
    (const if_sOut_Car_par_type x, const if_sOut_Car_par_type y);
inline void if_sOut_Car_par_print
    (const if_sOut_Car_par_type x, FILE* f);
inline void if_sOut_Car_par_reset
    (if_sOut_Car_par_type& x);
#define if_sOut_Car_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_sOut_Car_par_type if_sOut_Car_par_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_sOut_Car_par_eq(x,y) if_sOut_Car_par_compare(x,y)==0
#define if_sOut_Car_par_ne(x,y) if_sOut_Car_par_compare(x,y)!=0

class if_sOut_Car_message : public IfMessage {

public:
  if_sOut_Car_message();
  if_sOut_Car_message(if_pid_type p1,if_InfoZone_type p2);
  if_sOut_Car_message(const if_sOut_Car_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sOut_Car_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sOkInit message interface 
 *
 */

#define if_sOkInit_signal 2


typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_sOkInit_par_type;

inline void if_sOkInit_par_copy
    (if_sOkInit_par_type& x, const if_sOkInit_par_type y);
inline int if_sOkInit_par_compare
    (const if_sOkInit_par_type x, const if_sOkInit_par_type y);
inline void if_sOkInit_par_print
    (const if_sOkInit_par_type x, FILE* f);
inline void if_sOkInit_par_reset
    (if_sOkInit_par_type& x);
#define if_sOkInit_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_sOkInit_par_type if_sOkInit_par_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_sOkInit_par_eq(x,y) if_sOkInit_par_compare(x,y)==0
#define if_sOkInit_par_ne(x,y) if_sOkInit_par_compare(x,y)!=0

class if_sOkInit_message : public IfMessage {

public:
  if_sOkInit_message();
  if_sOkInit_message(if_pid_type p1,if_InfoZone_type p2);
  if_sOkInit_message(const if_sOkInit_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sOkInit_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sInfoZone message interface 
 *
 */

#define if_sInfoZone_signal 3


typedef struct {
  if_pid_type p1;
  if_InfoZone_type p2;
} if_sInfoZone_par_type;

inline void if_sInfoZone_par_copy
    (if_sInfoZone_par_type& x, const if_sInfoZone_par_type y);
inline int if_sInfoZone_par_compare
    (const if_sInfoZone_par_type x, const if_sInfoZone_par_type y);
inline void if_sInfoZone_par_print
    (const if_sInfoZone_par_type x, FILE* f);
inline void if_sInfoZone_par_reset
    (if_sInfoZone_par_type& x);
#define if_sInfoZone_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_InfoZone_iterate(x.p2)
inline if_sInfoZone_par_type if_sInfoZone_par_make
    (if_pid_type p1,if_InfoZone_type p2);
#define if_sInfoZone_par_eq(x,y) if_sInfoZone_par_compare(x,y)==0
#define if_sInfoZone_par_ne(x,y) if_sInfoZone_par_compare(x,y)!=0

class if_sInfoZone_message : public IfMessage {

public:
  if_sInfoZone_message();
  if_sInfoZone_message(if_pid_type p1,if_InfoZone_type p2);
  if_sInfoZone_message(const if_sInfoZone_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sInfoZone_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sInitFreeSpot message interface 
 *
 */

#define if_sInitFreeSpot_signal 4


typedef struct {
  if_pid_type p1;
  if_i_spots_type p2;
} if_sInitFreeSpot_par_type;

inline void if_sInitFreeSpot_par_copy
    (if_sInitFreeSpot_par_type& x, const if_sInitFreeSpot_par_type y);
inline int if_sInitFreeSpot_par_compare
    (const if_sInitFreeSpot_par_type x, const if_sInitFreeSpot_par_type y);
inline void if_sInitFreeSpot_par_print
    (const if_sInitFreeSpot_par_type x, FILE* f);
inline void if_sInitFreeSpot_par_reset
    (if_sInitFreeSpot_par_type& x);
#define if_sInitFreeSpot_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_i_spots_iterate(x.p2)
inline if_sInitFreeSpot_par_type if_sInitFreeSpot_par_make
    (if_pid_type p1,if_i_spots_type p2);
#define if_sInitFreeSpot_par_eq(x,y) if_sInitFreeSpot_par_compare(x,y)==0
#define if_sInitFreeSpot_par_ne(x,y) if_sInitFreeSpot_par_compare(x,y)!=0

class if_sInitFreeSpot_message : public IfMessage {

public:
  if_sInitFreeSpot_message();
  if_sInitFreeSpot_message(if_pid_type p1,if_i_spots_type p2);
  if_sInitFreeSpot_message(const if_sInitFreeSpot_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sInitFreeSpot_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sInitTotalSpots message interface 
 *
 */

#define if_sInitTotalSpots_signal 5


typedef struct {
  if_pid_type p1;
  if_i_spots_type p2;
} if_sInitTotalSpots_par_type;

inline void if_sInitTotalSpots_par_copy
    (if_sInitTotalSpots_par_type& x, const if_sInitTotalSpots_par_type y);
inline int if_sInitTotalSpots_par_compare
    (const if_sInitTotalSpots_par_type x, const if_sInitTotalSpots_par_type y);
inline void if_sInitTotalSpots_par_print
    (const if_sInitTotalSpots_par_type x, FILE* f);
inline void if_sInitTotalSpots_par_reset
    (if_sInitTotalSpots_par_type& x);
#define if_sInitTotalSpots_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_i_spots_iterate(x.p2)
inline if_sInitTotalSpots_par_type if_sInitTotalSpots_par_make
    (if_pid_type p1,if_i_spots_type p2);
#define if_sInitTotalSpots_par_eq(x,y) if_sInitTotalSpots_par_compare(x,y)==0
#define if_sInitTotalSpots_par_ne(x,y) if_sInitTotalSpots_par_compare(x,y)!=0

class if_sInitTotalSpots_message : public IfMessage {

public:
  if_sInitTotalSpots_message();
  if_sInitTotalSpots_message(if_pid_type p1,if_i_spots_type p2);
  if_sInitTotalSpots_message(const if_sInitTotalSpots_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sInitTotalSpots_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sReqInfo message interface 
 *
 */

#define if_sReqInfo_signal 6


typedef struct {
  if_pid_type p1;
} if_sReqInfo_par_type;

inline void if_sReqInfo_par_copy
    (if_sReqInfo_par_type& x, const if_sReqInfo_par_type y);
inline int if_sReqInfo_par_compare
    (const if_sReqInfo_par_type x, const if_sReqInfo_par_type y);
inline void if_sReqInfo_par_print
    (const if_sReqInfo_par_type x, FILE* f);
inline void if_sReqInfo_par_reset
    (if_sReqInfo_par_type& x);
#define if_sReqInfo_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sReqInfo_par_type if_sReqInfo_par_make
    (if_pid_type p1);
#define if_sReqInfo_par_eq(x,y) if_sReqInfo_par_compare(x,y)==0
#define if_sReqInfo_par_ne(x,y) if_sReqInfo_par_compare(x,y)!=0

class if_sReqInfo_message : public IfMessage {

public:
  if_sReqInfo_message();
  if_sReqInfo_message(if_pid_type p1);
  if_sReqInfo_message(const if_sReqInfo_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sReqInfo_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sLoopInductive_Zone message interface 
 *
 */

#define if_sLoopInductive_Zone_signal 7


typedef struct {
  if_pid_type p1;
} if_sLoopInductive_Zone_par_type;

inline void if_sLoopInductive_Zone_par_copy
    (if_sLoopInductive_Zone_par_type& x, const if_sLoopInductive_Zone_par_type y);
inline int if_sLoopInductive_Zone_par_compare
    (const if_sLoopInductive_Zone_par_type x, const if_sLoopInductive_Zone_par_type y);
inline void if_sLoopInductive_Zone_par_print
    (const if_sLoopInductive_Zone_par_type x, FILE* f);
inline void if_sLoopInductive_Zone_par_reset
    (if_sLoopInductive_Zone_par_type& x);
#define if_sLoopInductive_Zone_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sLoopInductive_Zone_par_type if_sLoopInductive_Zone_par_make
    (if_pid_type p1);
#define if_sLoopInductive_Zone_par_eq(x,y) if_sLoopInductive_Zone_par_compare(x,y)==0
#define if_sLoopInductive_Zone_par_ne(x,y) if_sLoopInductive_Zone_par_compare(x,y)!=0

class if_sLoopInductive_Zone_message : public IfMessage {

public:
  if_sLoopInductive_Zone_message();
  if_sLoopInductive_Zone_message(if_pid_type p1);
  if_sLoopInductive_Zone_message(const if_sLoopInductive_Zone_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sLoopInductive_Zone_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sIR1_Zone message interface 
 *
 */

#define if_sIR1_Zone_signal 8


typedef struct {
  if_pid_type p1;
} if_sIR1_Zone_par_type;

inline void if_sIR1_Zone_par_copy
    (if_sIR1_Zone_par_type& x, const if_sIR1_Zone_par_type y);
inline int if_sIR1_Zone_par_compare
    (const if_sIR1_Zone_par_type x, const if_sIR1_Zone_par_type y);
inline void if_sIR1_Zone_par_print
    (const if_sIR1_Zone_par_type x, FILE* f);
inline void if_sIR1_Zone_par_reset
    (if_sIR1_Zone_par_type& x);
#define if_sIR1_Zone_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sIR1_Zone_par_type if_sIR1_Zone_par_make
    (if_pid_type p1);
#define if_sIR1_Zone_par_eq(x,y) if_sIR1_Zone_par_compare(x,y)==0
#define if_sIR1_Zone_par_ne(x,y) if_sIR1_Zone_par_compare(x,y)!=0

class if_sIR1_Zone_message : public IfMessage {

public:
  if_sIR1_Zone_message();
  if_sIR1_Zone_message(if_pid_type p1);
  if_sIR1_Zone_message(const if_sIR1_Zone_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sIR1_Zone_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sIR2_Zone message interface 
 *
 */

#define if_sIR2_Zone_signal 9


typedef struct {
  if_pid_type p1;
} if_sIR2_Zone_par_type;

inline void if_sIR2_Zone_par_copy
    (if_sIR2_Zone_par_type& x, const if_sIR2_Zone_par_type y);
inline int if_sIR2_Zone_par_compare
    (const if_sIR2_Zone_par_type x, const if_sIR2_Zone_par_type y);
inline void if_sIR2_Zone_par_print
    (const if_sIR2_Zone_par_type x, FILE* f);
inline void if_sIR2_Zone_par_reset
    (if_sIR2_Zone_par_type& x);
#define if_sIR2_Zone_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sIR2_Zone_par_type if_sIR2_Zone_par_make
    (if_pid_type p1);
#define if_sIR2_Zone_par_eq(x,y) if_sIR2_Zone_par_compare(x,y)==0
#define if_sIR2_Zone_par_ne(x,y) if_sIR2_Zone_par_compare(x,y)!=0

class if_sIR2_Zone_message : public IfMessage {

public:
  if_sIR2_Zone_message();
  if_sIR2_Zone_message(if_pid_type p1);
  if_sIR2_Zone_message(const if_sIR2_Zone_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sIR2_Zone_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sIR3_Zone message interface 
 *
 */

#define if_sIR3_Zone_signal 10


typedef struct {
  if_pid_type p1;
} if_sIR3_Zone_par_type;

inline void if_sIR3_Zone_par_copy
    (if_sIR3_Zone_par_type& x, const if_sIR3_Zone_par_type y);
inline int if_sIR3_Zone_par_compare
    (const if_sIR3_Zone_par_type x, const if_sIR3_Zone_par_type y);
inline void if_sIR3_Zone_par_print
    (const if_sIR3_Zone_par_type x, FILE* f);
inline void if_sIR3_Zone_par_reset
    (if_sIR3_Zone_par_type& x);
#define if_sIR3_Zone_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sIR3_Zone_par_type if_sIR3_Zone_par_make
    (if_pid_type p1);
#define if_sIR3_Zone_par_eq(x,y) if_sIR3_Zone_par_compare(x,y)==0
#define if_sIR3_Zone_par_ne(x,y) if_sIR3_Zone_par_compare(x,y)!=0

class if_sIR3_Zone_message : public IfMessage {

public:
  if_sIR3_Zone_message();
  if_sIR3_Zone_message(if_pid_type p1);
  if_sIR3_Zone_message(const if_sIR3_Zone_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sIR3_Zone_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sIR4_Zone message interface 
 *
 */

#define if_sIR4_Zone_signal 11


typedef struct {
  if_pid_type p1;
} if_sIR4_Zone_par_type;

inline void if_sIR4_Zone_par_copy
    (if_sIR4_Zone_par_type& x, const if_sIR4_Zone_par_type y);
inline int if_sIR4_Zone_par_compare
    (const if_sIR4_Zone_par_type x, const if_sIR4_Zone_par_type y);
inline void if_sIR4_Zone_par_print
    (const if_sIR4_Zone_par_type x, FILE* f);
inline void if_sIR4_Zone_par_reset
    (if_sIR4_Zone_par_type& x);
#define if_sIR4_Zone_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sIR4_Zone_par_type if_sIR4_Zone_par_make
    (if_pid_type p1);
#define if_sIR4_Zone_par_eq(x,y) if_sIR4_Zone_par_compare(x,y)==0
#define if_sIR4_Zone_par_ne(x,y) if_sIR4_Zone_par_compare(x,y)!=0

class if_sIR4_Zone_message : public IfMessage {

public:
  if_sIR4_Zone_message();
  if_sIR4_Zone_message(if_pid_type p1);
  if_sIR4_Zone_message(const if_sIR4_Zone_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sIR4_Zone_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sOkInitPid message interface 
 *
 */

#define if_sOkInitPid_signal 12


typedef struct {
  if_pid_type p1;
} if_sOkInitPid_par_type;

inline void if_sOkInitPid_par_copy
    (if_sOkInitPid_par_type& x, const if_sOkInitPid_par_type y);
inline int if_sOkInitPid_par_compare
    (const if_sOkInitPid_par_type x, const if_sOkInitPid_par_type y);
inline void if_sOkInitPid_par_print
    (const if_sOkInitPid_par_type x, FILE* f);
inline void if_sOkInitPid_par_reset
    (if_sOkInitPid_par_type& x);
#define if_sOkInitPid_par_iterate(x)\
  if_pid_iterate(x.p1)
inline if_sOkInitPid_par_type if_sOkInitPid_par_make
    (if_pid_type p1);
#define if_sOkInitPid_par_eq(x,y) if_sOkInitPid_par_compare(x,y)==0
#define if_sOkInitPid_par_ne(x,y) if_sOkInitPid_par_compare(x,y)!=0

class if_sOkInitPid_message : public IfMessage {

public:
  if_sOkInitPid_message();
  if_sOkInitPid_message(if_pid_type p1);
  if_sOkInitPid_message(const if_sOkInitPid_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sOkInitPid_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};


/* 
 * sInitPidCtrl message interface 
 *
 */

#define if_sInitPidCtrl_signal 13


typedef struct {
  if_pid_type p1;
  if_pid_type p2;
} if_sInitPidCtrl_par_type;

inline void if_sInitPidCtrl_par_copy
    (if_sInitPidCtrl_par_type& x, const if_sInitPidCtrl_par_type y);
inline int if_sInitPidCtrl_par_compare
    (const if_sInitPidCtrl_par_type x, const if_sInitPidCtrl_par_type y);
inline void if_sInitPidCtrl_par_print
    (const if_sInitPidCtrl_par_type x, FILE* f);
inline void if_sInitPidCtrl_par_reset
    (if_sInitPidCtrl_par_type& x);
#define if_sInitPidCtrl_par_iterate(x)\
  if_pid_iterate(x.p1)\
  if_pid_iterate(x.p2)
inline if_sInitPidCtrl_par_type if_sInitPidCtrl_par_make
    (if_pid_type p1,if_pid_type p2);
#define if_sInitPidCtrl_par_eq(x,y) if_sInitPidCtrl_par_compare(x,y)==0
#define if_sInitPidCtrl_par_ne(x,y) if_sInitPidCtrl_par_compare(x,y)!=0

class if_sInitPidCtrl_message : public IfMessage {

public:
  if_sInitPidCtrl_message();
  if_sInitPidCtrl_message(if_pid_type p1,if_pid_type p2);
  if_sInitPidCtrl_message(const if_sInitPidCtrl_message&);

  virtual int compare(const IfMessage*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfMessage* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  static const char* NAME;

public:
  if_sInitPidCtrl_par_type m_par;

public:
  virtual int GetParSize() const { return sizeof(m_par); }
  virtual void* GetParAddress() const { return (void*)&m_par; }

};













/* 
 * ParkingSystem [system] instance interface 
 *
 */

class if_ParkingSystem_instance : public IfInstance { 

  public:
    if_ParkingSystem_instance(if_pid_type = 0, IfQueue* = IfQueue::NIL);
    if_ParkingSystem_instance(const if_ParkingSystem_instance&);

  protected:

};


/* 
 * pZone instance interface 
 *
 */
 
#define if_pZone_process 10


typedef struct {
  if_pid_type PARENT;
} if_pZone_par_type;

inline void if_pZone_par_copy
    (if_pZone_par_type& x, const if_pZone_par_type y);
inline int if_pZone_par_compare
    (const if_pZone_par_type x, const if_pZone_par_type y);
inline void if_pZone_par_print
    (const if_pZone_par_type x, FILE* f);
inline void if_pZone_par_reset
    (if_pZone_par_type& x);
#define if_pZone_par_iterate(x)\
  if_pid_iterate(x.PARENT)
inline if_pZone_par_type if_pZone_par_make
    (if_pid_type PARENT);
#define if_pZone_par_eq(x,y) if_pZone_par_compare(x,y)==0
#define if_pZone_par_ne(x,y) if_pZone_par_compare(x,y)!=0


typedef struct {
  if_pid_type OFFSPRING;
  if_pid_type SENDER;
  if_boolean_type RTDS_skip;
  if_boolean_type RTDS_stop;
  if_i_spots_type p_freeSpots;
  if_i_spots_type p_totalSpots;
  if_i_spots_type TmpfreeSpots;
  if_i_spots_type TmptotalSpots;
  if_i_spots_type freeSpots;
  if_i_spots_type totalSpots;
  if_pid_type PidZone;
  if_pid_type pid_Ctrl;
  if_pid_type pidCtrl;
  if_InfoZone_type infoTableZone;
} if_pZone_var_type;

inline void if_pZone_var_copy
    (if_pZone_var_type& x, const if_pZone_var_type y);
inline int if_pZone_var_compare
    (const if_pZone_var_type x, const if_pZone_var_type y);
inline void if_pZone_var_print
    (const if_pZone_var_type x, FILE* f);
inline void if_pZone_var_reset
    (if_pZone_var_type& x);
#define if_pZone_var_iterate(x)\
  if_pid_iterate(x.OFFSPRING)\
  if_pid_iterate(x.SENDER)\
  if_boolean_iterate(x.RTDS_skip)\
  if_boolean_iterate(x.RTDS_stop)\
  if_i_spots_iterate(x.p_freeSpots)\
  if_i_spots_iterate(x.p_totalSpots)\
  if_i_spots_iterate(x.TmpfreeSpots)\
  if_i_spots_iterate(x.TmptotalSpots)\
  if_i_spots_iterate(x.freeSpots)\
  if_i_spots_iterate(x.totalSpots)\
  if_pid_iterate(x.PidZone)\
  if_pid_iterate(x.pid_Ctrl)\
  if_pid_iterate(x.pidCtrl)\
  if_InfoZone_iterate(x.infoTableZone)
inline if_pZone_var_type if_pZone_var_make
    (if_pid_type OFFSPRING,if_pid_type SENDER,if_boolean_type RTDS_skip,if_boolean_type RTDS_stop,if_i_spots_type p_freeSpots,if_i_spots_type p_totalSpots,if_i_spots_type TmpfreeSpots,if_i_spots_type TmptotalSpots,if_i_spots_type freeSpots,if_i_spots_type totalSpots,if_pid_type PidZone,if_pid_type pid_Ctrl,if_pid_type pidCtrl,if_InfoZone_type infoTableZone);
#define if_pZone_var_eq(x,y) if_pZone_var_compare(x,y)==0
#define if_pZone_var_ne(x,y) if_pZone_var_compare(x,y)!=0


typedef struct {
  if_integer_type top;
} if_pZone_ctl_type;

inline void if_pZone_ctl_copy
    (if_pZone_ctl_type& x, const if_pZone_ctl_type y);
inline int if_pZone_ctl_compare
    (const if_pZone_ctl_type x, const if_pZone_ctl_type y);
inline void if_pZone_ctl_print
    (const if_pZone_ctl_type x, FILE* f);
inline void if_pZone_ctl_reset
    (if_pZone_ctl_type& x);
#define if_pZone_ctl_iterate(x)\
  if_integer_iterate(x.top)
inline if_pZone_ctl_type if_pZone_ctl_make
    (if_integer_type top);
#define if_pZone_ctl_eq(x,y) if_pZone_ctl_compare(x,y)==0
#define if_pZone_ctl_ne(x,y) if_pZone_ctl_compare(x,y)!=0

class if_pZone_instance : public if_ParkingSystem_instance {

public:
  if_pZone_instance();
  if_pZone_instance(if_pid_type PARENT);
  if_pZone_instance(const if_pZone_instance&);

  inline int GetSP() const { return m_ctl.top; }	// still used by observer operator "instate" -> only working without concurrent SMs

public:
  virtual const char* getState() const;
  virtual int is(const unsigned) const;

public:
  virtual int compare(const IfInstance*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfInstance* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public: 
  virtual void reset();
  virtual void iterate(IfIterator*);
  virtual void copy(const IfInstance*);

public:
  static const char* NAME;

public:
  inline if_pid_type& PARENT()
    { return m_par.PARENT; }
  
  inline if_pid_type& OFFSPRING()
    { return m_var.OFFSPRING; }
  inline if_pid_type& SENDER()
    { return m_var.SENDER; }
  inline if_boolean_type& RTDS_skip()
    { return m_var.RTDS_skip; }
  inline if_boolean_type& RTDS_stop()
    { return m_var.RTDS_stop; }
  inline if_i_spots_type& p_freeSpots()
    { return m_var.p_freeSpots; }
  inline if_i_spots_type& p_totalSpots()
    { return m_var.p_totalSpots; }
  inline if_i_spots_type& TmpfreeSpots()
    { return m_var.TmpfreeSpots; }
  inline if_i_spots_type& TmptotalSpots()
    { return m_var.TmptotalSpots; }
  inline if_i_spots_type& freeSpots()
    { return m_var.freeSpots; }
  inline if_i_spots_type& totalSpots()
    { return m_var.totalSpots; }
  inline if_pid_type& PidZone()
    { return m_var.PidZone; }
  inline if_pid_type& pid_Ctrl()
    { return m_var.pid_Ctrl; }
  inline if_pid_type& pidCtrl()
    { return m_var.pidCtrl; }
  inline if_InfoZone_type& infoTableZone()
    { return m_var.infoTableZone; }
  

private: 
  if_pZone_par_type m_par;  /* parameters */ 
  if_pZone_var_type m_var;  /* variables */
  if_pZone_ctl_type m_ctl;  /* control */

private:  
  inline int input(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1)
      ok |= (STATE[m_ctl.top].sigtab[signal] & 1);
    return ok;
  }
  inline int save(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1) 
      ok |= (STATE[m_ctl.top].sigtab[signal] & 2);
    return ok;
  }

private:
         void fire();
//         void tpc();
         void dispatch(IfMessage*, int);
  inline void nextstate();

         void _top_dispatch(IfMessage*);

         void _RTDS_START_dispatch(IfMessage*);

         void _RTDS_START_1_fire(IfMessage*);
  inline void _RTDS_START_1a_fire();
  inline void _RTDS_START_1b_fire();
  inline void _RTDS_START_1c_fire();
  inline void _RTDS_START_1d_fire();
  inline void _RTDS_START_1e_fire();


         void _Idle_dispatch(IfMessage*);

         void _Idle_1_fire(IfMessage*);
  inline void _Idle_1a_fire(IfMessage*);
  inline void _Idle_1b_fire();
  inline void _Idle_1c_fire();

         void _Idle_2_fire(IfMessage*);
  inline void _Idle_2a_fire(IfMessage*);

  inline void _Idle_2b_fire();

         void _Idle_3_fire(IfMessage*);
  inline void _Idle_3a_fire(IfMessage*);
  inline void _Idle_3b_fire();
  inline void _Idle_3c_fire();
  inline void _Idle_3d_fire();

         void _Idle_4_fire(IfMessage*);
  inline void _Idle_4a_fire(IfMessage*);
  inline void _Idle_4b_fire();
  inline void _Idle_4c_fire();
  inline void _Idle_4d_fire();

         void _Idle_5_fire(IfMessage*);
  inline void _Idle_5a_fire(IfMessage*);

  inline void _Idle_5b_fire();

         void _Idle_6_fire(IfMessage*);
  inline void _Idle_6a_fire(IfMessage*);
  inline void _Idle_6b_fire();
  inline void _Idle_6c_fire();
  inline void _Idle_6d_fire();


         void _WaitSensorIR4_dispatch(IfMessage*);

         void _WaitSensorIR4_1_fire(IfMessage*);
  inline void _WaitSensorIR4_1a_fire(IfMessage*);

  inline void _WaitSensorIR4_1b_fire();


         void _WaitSensorIR2_dispatch(IfMessage*);

         void _WaitSensorIR2_1_fire(IfMessage*);
  inline void _WaitSensorIR2_1a_fire(IfMessage*);

  inline void _WaitSensorIR2_1b_fire();


         void _sEvaluatingFreeSpots_dispatch(IfMessage*);

         void _sEvaluatingFreeSpots_1_fire(IfMessage*);
  inline void _sEvaluatingFreeSpots_1a_fire();
  inline void _sEvaluatingFreeSpots_1b_fire();

         void _sEvaluatingFreeSpots_2_fire(IfMessage*);
  inline void _sEvaluatingFreeSpots_2a_fire();
  inline void _sEvaluatingFreeSpots_2b_fire();
  inline void _sEvaluatingFreeSpots_2c_fire();
  inline void _sEvaluatingFreeSpots_2d_fire();


         void _VerifyIsaCarEntering_dispatch(IfMessage*);

         void _VerifyIsaCarEntering_1_fire(IfMessage*);
  inline void _VerifyIsaCarEntering_1a_fire(IfMessage*);
  inline void _VerifyIsaCarEntering_1b_fire();
  inline void _VerifyIsaCarEntering_1c_fire();


         void _sEvaluatingTotalSpots_dispatch(IfMessage*);

         void _sEvaluatingTotalSpots_1_fire(IfMessage*);
  inline void _sEvaluatingTotalSpots_1a_fire();
  inline void _sEvaluatingTotalSpots_1b_fire();

         void _sEvaluatingTotalSpots_2_fire(IfMessage*);
  inline void _sEvaluatingTotalSpots_2a_fire();
  inline void _sEvaluatingTotalSpots_2b_fire();
  inline void _sEvaluatingTotalSpots_2c_fire();
  inline void _sEvaluatingTotalSpots_2d_fire();


         void _VerifyIsaCarOut_dispatch(IfMessage*);

         void _VerifyIsaCarOut_1_fire(IfMessage*);
  inline void _VerifyIsaCarOut_1a_fire(IfMessage*);
  inline void _VerifyIsaCarOut_1b_fire();
  inline void _VerifyIsaCarOut_1c_fire();
  inline void _VerifyIsaCarOut_1d_fire();


private:
  typedef void (if_pZone_instance::*dispatcher)(IfMessage*);
//  typedef void (if_pZone_instance::*tpcchecker)();
  static if_state<15,dispatcher/*,tpcchecker*/> STATE[];


};



/* 
 * RTDS_start_process instance interface 
 *
 */
 
#define if_RTDS_start_process_process 11



typedef if_void_type if_RTDS_start_process_par_type;

#define if_RTDS_start_process_par_copy(x,y) if_void_copy(x,y)
#define if_RTDS_start_process_par_compare(x,y) if_void_compare(x,y)
#define if_RTDS_start_process_par_print(x,f) if_void_print(x,f)
#define if_RTDS_start_process_par_print_xml(x,b) if_void_print_xml(x,b)
#define if_RTDS_start_process_par_reset(x) if_void_reset(x)
#define if_RTDS_start_process_par_iterate(x) if_void_iterate(x)
#define if_RTDS_start_process_par_eq(x,y) if_RTDS_start_process_par_compare(x,y)==0
#define if_RTDS_start_process_par_ne(x,y) if_RTDS_start_process_par_compare(x,y)!=0



typedef if_void_type if_RTDS_start_process_var_type;

#define if_RTDS_start_process_var_copy(x,y) if_void_copy(x,y)
#define if_RTDS_start_process_var_compare(x,y) if_void_compare(x,y)
#define if_RTDS_start_process_var_print(x,f) if_void_print(x,f)
#define if_RTDS_start_process_var_print_xml(x,b) if_void_print_xml(x,b)
#define if_RTDS_start_process_var_reset(x) if_void_reset(x)
#define if_RTDS_start_process_var_iterate(x) if_void_iterate(x)
#define if_RTDS_start_process_var_eq(x,y) if_RTDS_start_process_var_compare(x,y)==0
#define if_RTDS_start_process_var_ne(x,y) if_RTDS_start_process_var_compare(x,y)!=0


typedef struct {
  if_integer_type top;
} if_RTDS_start_process_ctl_type;

inline void if_RTDS_start_process_ctl_copy
    (if_RTDS_start_process_ctl_type& x, const if_RTDS_start_process_ctl_type y);
inline int if_RTDS_start_process_ctl_compare
    (const if_RTDS_start_process_ctl_type x, const if_RTDS_start_process_ctl_type y);
inline void if_RTDS_start_process_ctl_print
    (const if_RTDS_start_process_ctl_type x, FILE* f);
inline void if_RTDS_start_process_ctl_reset
    (if_RTDS_start_process_ctl_type& x);
#define if_RTDS_start_process_ctl_iterate(x)\
  if_integer_iterate(x.top)
inline if_RTDS_start_process_ctl_type if_RTDS_start_process_ctl_make
    (if_integer_type top);
#define if_RTDS_start_process_ctl_eq(x,y) if_RTDS_start_process_ctl_compare(x,y)==0
#define if_RTDS_start_process_ctl_ne(x,y) if_RTDS_start_process_ctl_compare(x,y)!=0

class if_RTDS_start_process_instance : public if_ParkingSystem_instance {

public:
  
  if_RTDS_start_process_instance();
  if_RTDS_start_process_instance(const if_RTDS_start_process_instance&);

  inline int GetSP() const { return m_ctl.top; }	// still used by observer operator "instate" -> only working without concurrent SMs

public:
  virtual const char* getState() const;
  virtual int is(const unsigned) const;

public:
  virtual int compare(const IfInstance*) const;
  virtual unsigned long hash(const unsigned long) const;
  virtual IfInstance* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public: 
  virtual void reset();
  virtual void iterate(IfIterator*);
  virtual void copy(const IfInstance*);

public:
  static const char* NAME;

public:
  
  

private: 
  if_RTDS_start_process_par_type m_par;  /* parameters */ 
  if_RTDS_start_process_var_type m_var;  /* variables */
  if_RTDS_start_process_ctl_type m_ctl;  /* control */

private:  
  inline int input(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1)
      ok |= (STATE[m_ctl.top].sigtab[signal] & 1);
    return ok;
  }
  inline int save(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1) 
      ok |= (STATE[m_ctl.top].sigtab[signal] & 2);
    return ok;
  }

private:
         void fire();
//         void tpc();
         void dispatch(IfMessage*, int);
  inline void nextstate();

         void _top_dispatch(IfMessage*);

         void _RTDS_START_dispatch(IfMessage*);

         void _RTDS_START_1_fire(IfMessage*);
  inline void _RTDS_START_1a_fire();
  inline void _RTDS_START_1b_fire();
  inline void _RTDS_START_1c_fire();


private:
  typedef void (if_RTDS_start_process_instance::*dispatcher)(IfMessage*);
//  typedef void (if_RTDS_start_process_instance::*tpcchecker)();
  static if_state<15,dispatcher/*,tpcchecker*/> STATE[];


};




/* 
 * obsInitPid instance interface 
 *
 */
 
#define if_obsInitPid_observer 12


typedef struct {
  if_pid_type pidSender;
  if_pid_type pidCtrl;
  if_pid_type pidZone;
  if_integer_type tmpVar;
} if_obsInitPid_var_type;

inline void if_obsInitPid_var_copy
    (if_obsInitPid_var_type& x, const if_obsInitPid_var_type y);
inline int if_obsInitPid_var_compare
    (const if_obsInitPid_var_type x, const if_obsInitPid_var_type y);
inline void if_obsInitPid_var_print
    (const if_obsInitPid_var_type x, FILE* f);
inline void if_obsInitPid_var_reset
    (if_obsInitPid_var_type& x);
#define if_obsInitPid_var_iterate(x)\
  if_pid_iterate(x.pidSender)\
  if_pid_iterate(x.pidCtrl)\
  if_pid_iterate(x.pidZone)\
  if_integer_iterate(x.tmpVar)
inline if_obsInitPid_var_type if_obsInitPid_var_make
    (if_pid_type pidSender,if_pid_type pidCtrl,if_pid_type pidZone,if_integer_type tmpVar);
#define if_obsInitPid_var_eq(x,y) if_obsInitPid_var_compare(x,y)==0
#define if_obsInitPid_var_ne(x,y) if_obsInitPid_var_compare(x,y)!=0


typedef struct {
  if_integer_type top;
} if_obsInitPid_ctl_type;

inline void if_obsInitPid_ctl_copy
    (if_obsInitPid_ctl_type& x, const if_obsInitPid_ctl_type y);
inline int if_obsInitPid_ctl_compare
    (const if_obsInitPid_ctl_type x, const if_obsInitPid_ctl_type y);
inline void if_obsInitPid_ctl_print
    (const if_obsInitPid_ctl_type x, FILE* f);
inline void if_obsInitPid_ctl_reset
    (if_obsInitPid_ctl_type& x);
#define if_obsInitPid_ctl_iterate(x)\
  if_integer_iterate(x.top)
inline if_obsInitPid_ctl_type if_obsInitPid_ctl_make
    (if_integer_type top);
#define if_obsInitPid_ctl_eq(x,y) if_obsInitPid_ctl_compare(x,y)==0
#define if_obsInitPid_ctl_ne(x,y) if_obsInitPid_ctl_compare(x,y)!=0

class if_obsInitPid_instance : public IfObserverInstance {

public:
  
  if_obsInitPid_instance();
  if_obsInitPid_instance(const if_obsInitPid_instance&);

  inline int GetSP() const { return m_ctl.top; }	// still used by observer operator "instate" -> only working without concurrent SMs

public:
  virtual const char* getState() const;
  virtual int is(const unsigned) const;

public:
  virtual int compare(const IfInstance*) const;
  virtual long unsigned hash(const unsigned long) const;
  virtual IfInstance* copy() const;
  virtual void print(FILE*) const;
  virtual void printXML(std::ostream&) const;

public:
  virtual int isObsSuccess() const { return STATE[m_ctl.top].flags & OSUCCESS; }
  virtual int isObsError() const { return STATE[m_ctl.top].flags & OERROR; }

public: 
  virtual void reset();
  virtual void iterate(IfIterator*);
  virtual void copy(const IfInstance*);

public:
  static const char* NAME;

public:
  inline if_pid_type& pidSender()
    { return m_var.pidSender; }
  inline if_pid_type& pidCtrl()
    { return m_var.pidCtrl; }
  inline if_pid_type& pidZone()
    { return m_var.pidZone; }
  inline if_integer_type& tmpVar()
    { return m_var.tmpVar; }
  

private:
  if_obsInitPid_var_type m_var;  /* variables */
  if_obsInitPid_ctl_type m_ctl;  /* control */

private:  
  inline int input(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1)
      ok |= (STATE[m_ctl.top].sigtab[signal] & 1);
    return ok;
  }
  inline int save(unsigned signal) const {
    int ok = 0;
    if (m_ctl.top != -1) 
      ok |= (STATE[m_ctl.top].sigtab[signal] & 2);
    return ok;
  }

private:
         void fire();
         void dispatch(IfMessage*, int);
  inline void nextstate();

         void _top_dispatch(IfMessage*);

         void _RTDS_START_dispatch(IfMessage*);

         void _RTDS_START_1_fire(IfMessage*);

  inline void _RTDS_START_1a_fire();


         void _sOk_dispatch(IfMessage*);

         void _sOk_1_fire(IfMessage*);
  inline void _sOk_1a_fire();
  inline void _sOk_1b_fire();


         void _Idle_dispatch(IfMessage*);

         void _Idle_1_fire(IfMessage*);
  inline void _Idle_1a_fire(IfMessage* X);

  inline void _Idle_1b_fire();

         void _Idle_2_fire(IfMessage*);
  inline void _Idle_2a_fire(IfMessage* X);
  inline void _Idle_2b_fire();
  inline void _Idle_2c_fire();


         void _RTDS_decision_SYMB10_dispatch(IfMessage*);

         void _RTDS_decision_SYMB10_1_fire(IfMessage*);

  inline void _RTDS_decision_SYMB10_1a_fire();

         void _RTDS_decision_SYMB10_2_fire(IfMessage*);
  inline void _RTDS_decision_SYMB10_2a_fire();
  inline void _RTDS_decision_SYMB10_2b_fire();


         void _sError_dispatch(IfMessage*);

         void _sError_1_fire(IfMessage*);
  inline void _sError_1a_fire();
  inline void _sError_1b_fire();


         void _DEAD_dispatch(IfMessage*);

private:
  typedef void (if_obsInitPid_instance::*dispatcher)(IfMessage*);
  static if_state<15,dispatcher> STATE[];


};




