//
// Copyright (c) 2013 Zvonimir Rakamaric (zvonimir@cs.utah.edu),
//                    Michael Emmi (michael.emmi@gmail.com)
// This file is distributed under the MIT License. See LICENSE for details.
//
#include "smack/SmackRep.h"
#include "smack/SmackRep2dMem.h"
#include "smack/SmackRepFlatMem.h"
#include "smack/SmackOptions.h"

namespace smack {

const string SmackRep::ALLOC = "$Alloc";
const string SmackRep::BLOCK_LBL = "$bb";
const string SmackRep::RET_VAR = "$r";
const string SmackRep::BOOL_VAR = "$b";
const string SmackRep::FLOAT_VAR = "$f";
const string SmackRep::PTR_VAR = "$p";
const string SmackRep::BOOL_TYPE = "bool";
const string SmackRep::FLOAT_TYPE = "float";
const string SmackRep::NULL_VAL = "$NULL";

const string SmackRep::ALLOCA = "$alloca";
const string SmackRep::MALLOC = "$malloc";
const string SmackRep::FREE = "$free";
const string SmackRep::MEMCPY = "$memcpy";

const string SmackRep::PTR = "$ptr";
const string SmackRep::STATIC = "$static";
const string SmackRep::OBJ = "$obj";
const string SmackRep::OFF = "$off";
const string SmackRep::PA = "$pa";

const string SmackRep::FP = "$fp";

const string SmackRep::B2P = "$b2p";
const string SmackRep::I2P = "$i2p";
const string SmackRep::P2I = "$p2i";
const string SmackRep::I2B = "$i2b";
const string SmackRep::B2I = "$b2i";

const string SmackRep::FP2SI = "$fp2si";
const string SmackRep::FP2UI = "$fp2ui";
const string SmackRep::SI2FP = "$si2fp";
const string SmackRep::UI2FP = "$ui2fp";

const string SmackRep::ADD = "$add";
const string SmackRep::SUB = "$sub";
const string SmackRep::MUL = "$mul";
const string SmackRep::SDIV = "$sdiv";
const string SmackRep::UDIV = "$udiv";
const string SmackRep::SREM = "$srem";
const string SmackRep::UREM = "$urem";
const string SmackRep::AND = "$and";
const string SmackRep::OR = "$or";
const string SmackRep::XOR = "$xor";
const string SmackRep::LSHR = "$lshr";
const string SmackRep::ASHR = "$ashr";
const string SmackRep::SHL = "$shl";

const string SmackRep::NAND = "$nand";
const string SmackRep::MAX = "$max";
const string SmackRep::MIN = "$min";
const string SmackRep::UMAX = "$umax";
const string SmackRep::UMIN = "$umin";

const string SmackRep::FADD = "$fadd";
const string SmackRep::FSUB = "$fsub";
const string SmackRep::FMUL = "$fmul";
const string SmackRep::FDIV = "$fdiv";
const string SmackRep::FREM = "$frem";

const string SmackRep::SGE = "$sge";
const string SmackRep::UGE = "$uge";
const string SmackRep::SLE = "$sle";
const string SmackRep::ULE = "$ule";
const string SmackRep::SLT = "$slt";
const string SmackRep::ULT = "$ult";
const string SmackRep::SGT = "$sgt";
const string SmackRep::UGT = "$ugt";

const string SmackRep::FFALSE = "$ffalse";
const string SmackRep::FOEQ = "$foeq";
const string SmackRep::FOGE = "$foge";
const string SmackRep::FOGT = "$fogt";
const string SmackRep::FOLE = "$fole";
const string SmackRep::FOLT = "$folt";
const string SmackRep::FONE = "$fone";
const string SmackRep::FORD = "$ford";
const string SmackRep::FTRUE = "$ftrue";
const string SmackRep::FUEQ = "$fueq";
const string SmackRep::FUGE = "$fuge";
const string SmackRep::FUGT = "$fugt";
const string SmackRep::FULE = "$fule";
const string SmackRep::FULT = "$fult";
const string SmackRep::FUNE = "$fune";
const string SmackRep::FUNO = "$funo";

// used for memory model debugging
const string SmackRep::MEM_OP = "$mop";
const string SmackRep::REC_MEM_OP = "boogie_si_record_mop";
const string SmackRep::MEM_OP_VAL = "$MOP";

const Expr* SmackRep::NUL = Expr::id(NULL_VAL);

const string SmackRep::BOOGIE_REC_PTR = "boogie_si_record_ptr";
const string SmackRep::BOOGIE_REC_OBJ = "boogie_si_record_obj";
const string SmackRep::BOOGIE_REC_INT = "boogie_si_record_int";

const string SmackRep::STATIC_INIT = "$static_init";

const string SmackRep::ARITHMETIC =
  "// Integer arithmetic\n"
  "function $add(p1:int, p2:int) returns (int) {p1 + p2}\n"
  "function $sub(p1:int, p2:int) returns (int) {p1 - p2}\n"
  "function $mul(p1:int, p2:int) returns (int) {p1 * p2}\n"
  "function $sdiv(p1:int, p2:int) returns (int);\n"
  "function $udiv(p1:int, p2:int) returns (int);\n"
  "function $srem(p1:int, p2:int) returns (int);\n"
  "function $urem(p1:int, p2:int) returns (int);\n"
  "function $and(p1:int, p2:int) returns (int);\n"
  "axiom $and(0,0) == 0;\n"
  "axiom $and(0,1) == 0;\n"
  "axiom $and(1,0) == 0;\n"
  "axiom $and(1,1) == 1;\n"
  "function $or(p1:int, p2:int) returns (int);\n"
  "axiom $or(0,0) == 0;\n"
  "axiom $or(0,1) == 1;\n"
  "axiom $or(1,0) == 1;\n"
  "axiom $or(1,1) == 1;\n"
  "function $xor(p1:int, p2:int) returns (int);\n"
  "axiom $xor(0,0) == 0;\n"
  "axiom $xor(0,1) == 1;\n"
  "axiom $xor(1,0) == 1;\n"
  "axiom $xor(1,1) == 0;\n"
  "function $lshr(p1:int, p2:int) returns (int);\n"
  "function $ashr(p1:int, p2:int) returns (int);\n"
  "function $shl(p1:int, p2:int) returns (int);\n"
  "function $ult(p1:int, p2:int) returns (bool) {p1 < p2}\n"
  "function $ugt(p1:int, p2:int) returns (bool) {p1 > p2}\n"
  "function $ule(p1:int, p2:int) returns (bool) {p1 <= p2}\n"
  "function $uge(p1:int, p2:int) returns (bool) {p1 >= p2}\n"
  "function $slt(p1:int, p2:int) returns (bool) {p1 < p2}\n"
  "function $sgt(p1:int, p2:int) returns (bool) {p1 > p2}\n"
  "function $sle(p1:int, p2:int) returns (bool) {p1 <= p2}\n"
  "function $sge(p1:int, p2:int) returns (bool) {p1 >= p2}\n"
  "function $nand(p1:int, p2:int) returns (int);\n"
  "function $max(p1:int, p2:int) returns (int);\n"
  "function $min(p1:int, p2:int) returns (int);\n"
  "function $umax(p1:int, p2:int) returns (int);\n"
  "function $umin(p1:int, p2:int) returns (int);\n"
  "function $i2b(i: int) returns (bool);\n"
  "axiom (forall i:int :: $i2b(i) <==> i != 0);\n"
  "axiom $i2b(0) == false;\n"
  "function $b2i(b: bool) returns (int);\n"
  "axiom $b2i(true) == 1;\n"
  "axiom $b2i(false) == 0;\n"
  "\n"
  "// Floating point\n"
  "type float;\n"
  "function $fp(a:int) returns (float);\n"
  "const $ffalse: float;\n"
  "const $ftrue: float;\n"
  "function $fadd(f1:float, f2:float) returns (float);\n"
  "function $fsub(f1:float, f2:float) returns (float);\n"
  "function $fmul(f1:float, f2:float) returns (float);\n"
  "function $fdiv(f1:float, f2:float) returns (float);\n"
  "function $frem(f1:float, f2:float) returns (float);\n"
  "function $foeq(f1:float, f2:float) returns (bool);\n"
  "function $foge(f1:float, f2:float) returns (bool);\n"
  "function $fogt(f1:float, f2:float) returns (bool);\n"
  "function $fole(f1:float, f2:float) returns (bool);\n"
  "function $folt(f1:float, f2:float) returns (bool);\n"
  "function $fone(f1:float, f2:float) returns (bool);\n"
  "function $ford(f1:float, f2:float) returns (bool);\n"
  "function $fueq(f1:float, f2:float) returns (bool);\n"
  "function $fuge(f1:float, f2:float) returns (bool);\n"
  "function $fugt(f1:float, f2:float) returns (bool);\n"
  "function $fule(f1:float, f2:float) returns (bool);\n"
  "function $fult(f1:float, f2:float) returns (bool);\n"
  "function $fune(f1:float, f2:float) returns (bool);\n"
  "function $funo(f1:float, f2:float) returns (bool);\n"
  "function $fp2si(f:float) returns (int);\n"
  "function $fp2ui(f:float) returns (int);\n"
  "function $si2fp(i:int) returns (float);\n"
  "function $ui2fp(i:int) returns (float);\n" ;

const string SmackRep::AUX_PROCS =
  "procedure boogie_si_record_int(i: int);\n";

const string SmackRep::MEMORY_DEBUG_SYMBOLS = 
  "type $mop;\n"
  "procedure boogie_si_record_mop(m: $mop);\n"
  "const $MOP: $mop;\n";

const int SmackRep::width = 0;

SmackRep* SmackRep::createRep(llvm::AliasAnalysis* aa) {
  if ( SmackOptions::MemoryModel == twodim )
    return new SmackRep2dMem(aa);
  else
    return new SmackRepFlatMem(aa);
}

// TODO Do the following functions belong here ?

string EscapeString(string s) {
  string Str(llvm::DOT::EscapeString(s));
  for (unsigned i = 0; i != Str.length(); ++i)
    switch (Str[i]) {
    case '\01':
      Str[i] = '_';
      break;
    }
  return Str;
}

Regex BPL_KW(
  "^(bool|int|false|true|old|forall|exists|requires|modifies|ensures|invariant"
  "|unique|finite|complete|type|const|function|axiom|var|procedure"
  "|implementation|where|returns|assume|assert|havoc|call|return|while"
  "|break|goto|if|else|div)$");
Regex SMACK_NAME(".*__SMACK_.*");
Regex PROC_IGNORE("^(malloc|free|llvm\\.memcpy\\..*|llvm\\.dbg\\..*)$");
Regex SMACK_ASSERT(".*__SMACK_assert.*");
Regex SMACK_ASSUME(".*__SMACK_assume.*");
Regex SMACK_YIELD(".*__SMACK_yield.*");
Regex SMACK_ASYNC_CALL(".*__SMACK_async_call.*");
Regex SMACK_REC_OBJ(".*__SMACK_record_obj.*");
Regex SMACK_REC_INT(".*__SMACK_record_int.*");
Regex SMACK_REC_PTR(".*__SMACK_record_ptr.*");

bool isBplKeyword(string s) {
  return BPL_KW.match(s);
}

bool SmackRep::isSmackName(string n) {
  return SMACK_NAME.match(n);
}

bool SmackRep::isProcIgnore(string n) {
  return PROC_IGNORE.match(n);
}

bool SmackRep::isSmackAssert(llvm::Function* f) {
  return SMACK_ASSERT.match(id(f));
}

bool SmackRep::isSmackAssume(llvm::Function* f) {
  return SMACK_ASSUME.match(id(f));
}

bool SmackRep::isSmackYield(llvm::Function* f) {
  return SMACK_YIELD.match(id(f));
}

bool SmackRep::isSmackAsyncCall(llvm::Function* f) {
  return SMACK_ASYNC_CALL.match(id(f));
}

bool SmackRep::isSmackRecObj(llvm::Function* f) {
  return SMACK_REC_OBJ.match(id(f));
}

bool SmackRep::isSmackRecInt(llvm::Function* f) {
  return SMACK_REC_INT.match(id(f));
}

bool SmackRep::isSmackRecPtr(llvm::Function* f) {
  return SMACK_REC_PTR.match(id(f));
}

bool SmackRep::isInt(const llvm::Type* t) {
  return t->isIntegerTy();
}

bool SmackRep::isInt(const llvm::Value* v) {
  return isInt(v->getType());
}

bool SmackRep::isBool(llvm::Type* t) {
  return t->isIntegerTy(1);
}

bool SmackRep::isBool(llvm::Value* v) {
  return isBool(v->getType());
}

bool SmackRep::isFloat(llvm::Type* t) {
  return t->isFloatingPointTy();
}

bool SmackRep::isFloat(llvm::Value* v) {
  return isFloat(v->getType());
}

string SmackRep::type(llvm::Type* t) {
  if (isBool(t))
    return BOOL_TYPE;
  else if (isFloat(t))
    return FLOAT_TYPE;
  else
    return getPtrType();
}

string SmackRep::type(llvm::Value* v) {
  return type(v->getType());
}

unsigned SmackRep::storageSize(llvm::Type* t) {
  return targetData->getTypeStoreSize(t);
}

unsigned SmackRep::fieldOffset(llvm::StructType* t, unsigned fieldNo) {
  return targetData->getStructLayout(t)->getElementOffset(fieldNo);
}

string SmackRep::memReg(unsigned i) {
  stringstream s;
  s << "$M." << i;
  return s.str();
}

const Expr* SmackRep::mem(const llvm::Value* v) {
  return Expr::sel(Expr::id(memReg(getRegion(v))), expr(v));
}

unsigned SmackRep::getRegion(const llvm::Value* v) {  
  for (unsigned i=0; i<memoryRegions.size(); ++i)
    if (!aliasAnalysis->isNoAlias(v, (const llvm::Value*) memoryRegions[i]))
      return i;

  memoryRegions.push_back(v);
  return memoryRegions.size()-1;
}

string SmackRep::memcpyCall(int dstReg, int srcReg) {
  stringstream s;
  s << "$memcpy." << dstReg << "." << srcReg;
  return s.str();
}

// const Expr* SmackRep::ptr(const Expr* obj, const Expr* off) {
//   return Expr::fn(PTR, obj, off);
// }
// 
// const Expr* SmackRep::obj(const Expr* e) {
//   return Expr::fn(OBJ, e);
// }
// 
// const Expr* SmackRep::off(const Expr* e) {
//   return Expr::fn(OFF, e);
// }

const Expr* SmackRep::i2p(const Expr* e) {
  return Expr::fn(I2P, e);
}

const Expr* SmackRep::p2i(const Expr* e) {
  return Expr::fn(P2I, e);
}

const Expr* SmackRep::b2p(const Expr* e) {
  return Expr::fn(B2P, e);
}

const Expr* SmackRep::i2b(const Expr* e) {
  return Expr::fn(I2B, e);
}

const Expr* SmackRep::b2i(const Expr* e) {
  return Expr::fn(B2I, e);
}

const Expr* SmackRep::fp2si(const Expr* e) {
  return Expr::fn(FP2SI, e);
}

const Expr* SmackRep::fp2ui(const Expr* e) {
  return Expr::fn(FP2UI, e);
}

const Expr* SmackRep::si2fp(const Expr* e) {
  return Expr::fn(SI2FP, e);
}

const Expr* SmackRep::ui2fp(const Expr* e) {
  return Expr::fn(UI2FP, e);
}

const Expr* SmackRep::pa(const Expr* e, int x, int y) {
  return pa(e, Expr::lit(x), Expr::lit(y));
}

const Expr* SmackRep::pa(const Expr* e, const Expr* x, int y) {
  return pa(e, x, Expr::lit(y));
}

const Expr* SmackRep::pa(const Expr* e, const Expr* x, const Expr* y) {
  return Expr::fn(PA, e, x, y);
}

const Expr* SmackRep::undef() {
  stringstream s;
  s << "$u." << uniqueUndefNum++;
  return Expr::id(s.str());
}

string SmackRep::id(const llvm::Value* v) {
  string name;

  if (v->hasName()) {
    name = v->getName().str();

  } else {
    assert(false && "expected named value.");

    // OLD NAME-HANDLING CODE
    // llvm::raw_string_ostream ss(name);
    // ss << *v;
    // name = name.substr(name.find("%"));
    // name = name.substr(0, name.find(" "));
  }
  name = EscapeString(name);

  if (isBplKeyword(name))
    name = name + "_";

  return name;
}

const Expr* SmackRep::lit(const llvm::Value* v) {
  if (const llvm::ConstantInt* ci = llvm::dyn_cast<const llvm::ConstantInt>(v)) {
    if (ci->getBitWidth() == 1)
      return Expr::lit(!ci->isZero());

    uint64_t val = ci->getLimitedValue();
    if (width > 0 && ci->isNegative())
      return Expr::fn(SUB, Expr::lit(0, width), Expr::lit(-val, width));
    else
      return Expr::lit(val, width);

  } else if (const llvm::ConstantFP* cf = llvm::dyn_cast<const llvm::ConstantFP>(v)) {

    // TODO encode floating point
    return Expr::fn(FP,Expr::lit((int) uniqueFpNum++));

  } else if (llvm::isa<llvm::ConstantPointerNull>(v))
    return Expr::lit(0, width);

  else
    return ptr2val(expr(v));
  // assert( false && "value type not supported" );
}

const Expr* SmackRep::lit(unsigned v) {
  // TODO why doesn't this one do the thing with negative as well?
  return Expr::lit(v, width);
}

const Expr* SmackRep::ptrArith(
  const llvm::Value* p, vector<llvm::Value*> ps, vector<llvm::Type*> ts) {

  assert(ps.size() > 0 && ps.size() == ts.size());

  const Expr* e = expr(p);

  for (unsigned i = 0; i < ps.size(); i++) {
    if (llvm::StructType* st = llvm::dyn_cast<llvm::StructType>(ts[i])) {

      assert(ps[i]->getType()->isIntegerTy()
             && ps[i]->getType()->getPrimitiveSizeInBits() == 32
             && "Illegal struct idx");

      // Get structure layout information...
      unsigned fieldNo =
        llvm::cast<llvm::ConstantInt>(ps[i])->getZExtValue();

      // Add in the offset, as calculated by the
      // structure layout info...
      e = pa(e, fieldOffset(st, fieldNo), 1);

    } else {
      llvm::Type* et =
        llvm::cast<llvm::SequentialType>(ts[i])->getElementType();
      e = pa(e, lit(ps[i]), storageSize(et));
    }
  }

  return e;
}

const Expr* SmackRep::expr(const llvm::Value* v) {
  using namespace llvm;

  if (const GlobalValue* g = dyn_cast<const GlobalValue>(v)) {
    assert(g->hasName());
    return ref2ptr(Expr::id(id(v)));

  } else if (v->hasName())
    return Expr::id(id(v));

  else if (const Constant* constant = dyn_cast<const Constant>(v)) {

    if (const ConstantExpr* constantExpr = dyn_cast<const ConstantExpr>(constant)) {

      if (constantExpr->getOpcode() == Instruction::GetElementPtr) {

        vector<llvm::Value*> ps;
        vector<llvm::Type*> ts;
        llvm::gep_type_iterator typeI = gep_type_begin(constantExpr);
        for (unsigned i = 1; i < constantExpr->getNumOperands(); i++, ++typeI) {
          ps.push_back(constantExpr->getOperand(i));
          ts.push_back(*typeI);
        }
        return ptrArith(constantExpr->getOperand(0), ps, ts);

      } else if (constantExpr->getOpcode() == Instruction::BitCast)

        // TODO: currently this is a noop instruction
        return expr(constantExpr->getOperand(0));

      else if (constantExpr->getOpcode() == Instruction::IntToPtr)

        // TODO test this out, formerly Expr::id("$UNDEF");
        return i2p(expr(constantExpr->getOperand(0)));

      else if (constantExpr->getOpcode() == Instruction::PtrToInt)

        // TODO test this out, formerly Expr::id("$UNDEF");
        return p2i(expr(constantExpr->getOperand(0)));

      else {
        DEBUG(errs() << "VALUE : " << *v << "\n");
        assert(false && "constant expression of this type not supported");
      }

    } else if (const ConstantInt* ci = dyn_cast<const ConstantInt>(constant)) {
      if (ci->getBitWidth() == 1)
        return Expr::lit(!ci->isZero());

      else return val2ptr(lit(ci));
      
    } else if (const ConstantFP* cf = dyn_cast<const ConstantFP>(constant)) {
      return val2ptr(lit(cf));

    } else if (constant->isNullValue())
      return val2ptr(lit((unsigned)0));

    else if (isa<UndefValue>(constant))
      return undef();

    else {
      DEBUG(errs() << "VALUE : " << *v << "\n");
      assert(false && "this type of constant not supported");
    }

  } else {
    DEBUG(errs() << "VALUE : " << *v << "\n");
    assert(false && "value of this type not supported");
  }
}

const Expr* SmackRep::op(llvm::BinaryOperator& o) {
  string op;
  switch (o.getOpcode()) {
    using llvm::Instruction;

  // Integer operations
  case Instruction::Add:
    op = ADD;
    break;
  case Instruction::Sub:
    op = SUB;
    break;
  case Instruction::Mul:
    op = MUL;
    break;
  case Instruction::SDiv:
    op = SDIV;
    break;
  case Instruction::UDiv:
    op = UDIV;
    break;
  case Instruction::SRem:
    op = SREM;
    break;
  case Instruction::URem:
    op = UREM;
    break;
  case Instruction::And:
    op = AND;
    break;
  case Instruction::Or:
    op = OR;
    break;
  case Instruction::Xor:
    op = XOR;
    break;
  case Instruction::LShr:
    op = LSHR;
    break;
  case Instruction::AShr:
    op = ASHR;
    break;
  case Instruction::Shl:
    op = SHL;
    break;

  // Floating point operations
  case Instruction::FAdd:
    op = FADD;
    break;
  case Instruction::FSub:
    op = FSUB;
    break;
  case Instruction::FMul:
    op = FMUL;
    break;
  case Instruction::FDiv:
    op = FDIV;
    break;
  case Instruction::FRem:
    op = FREM;
    break;
      
  default:
    assert(false && "unexpected predicate.");
  }
  llvm::Value
  *l = o.getOperand(0),
   *r = o.getOperand(1);

  const Expr* e = Expr::fn(op,
                           (isBool(l) ? b2i(expr(l)) : ptr2val(expr(l))),
                           (isBool(r) ? b2i(expr(r)) : ptr2val(expr(r))));

  return isBool(&o) ? i2b(e) : val2ptr(e);
}

const Expr* SmackRep::pred(llvm::CmpInst& ci) {
  const Expr* e = NULL;
  string o;
  const Expr
  *l = expr(ci.getOperand(0)),
   *r = expr(ci.getOperand(1));

  switch (ci.getPredicate()) {
    using llvm::CmpInst;

  // integer comparison
  case CmpInst::ICMP_EQ:
    e = Expr::eq(l, r);
    break;
  case CmpInst::ICMP_NE:
    e = Expr::neq(l, r);
    break;
  case CmpInst::ICMP_SGE:
    o = SGE;
    break;
  case CmpInst::ICMP_UGE:
    o = UGE;
    break;
  case CmpInst::ICMP_SLE:
    o = SLE;
    break;
  case CmpInst::ICMP_ULE:
    o = ULE;
    break;
  case CmpInst::ICMP_SLT:
    o = SLT;
    break;
  case CmpInst::ICMP_ULT:
    o = ULT;
    break;
  case CmpInst::ICMP_SGT:
    o = SGT;
    break;
  case CmpInst::ICMP_UGT:
    o = UGT;
    break;

  // floating point comparison 
  case CmpInst::FCMP_FALSE:
    o = FFALSE;
    break;
  case CmpInst::FCMP_OEQ:
    o = FOEQ;
    break;
  case CmpInst::FCMP_OGE:
    o = FOGE;
    break;
  case CmpInst::FCMP_OGT:
    o = FOGT;
    break;
  case CmpInst::FCMP_OLE:
    o = FOLE;
    break;
  case CmpInst::FCMP_OLT:
    o = FOLT;
    break;
  case CmpInst::FCMP_ONE:
    o = FONE;
    break;
  case CmpInst::FCMP_ORD:
    o = FORD;
    break;
  case CmpInst::FCMP_TRUE:
    o = FTRUE;
    break;
  case CmpInst::FCMP_UEQ:
    o = FUEQ;
    break;
  case CmpInst::FCMP_UGE:
    o = FUGE;
    break;
  case CmpInst::FCMP_UGT:
    o = FUGT;
    break;
  case CmpInst::FCMP_ULE:
    o = FULE;
    break;
  case CmpInst::FCMP_ULT:
    o = FULT;
    break;
  case CmpInst::FCMP_UNE:
    o = FUNE;
    break;
  case CmpInst::FCMP_UNO:
    o = FUNO;
    break;
  default:
    assert(false && "unexpected predicate.");
  }

  return e == NULL ? Expr::fn(o, ptr2val(l), ptr2val(r)) : e;
}

string SmackRep::getPrelude() {
  stringstream s;
  s << AUX_PROCS << endl;
  s << ARITHMETIC << endl;

  if (SmackOptions::MemoryModelDebug)
    s << MEMORY_DEBUG_SYMBOLS << endl;
    
  s << "// Memory region declarations";
  s << ": " << memoryRegions.size() << endl;
  for (unsigned i=0; i<memoryRegions.size(); ++i)
    s << "var " << memReg(i) 
      << ": [" << getPtrType() << "] " << getPtrType() << ";" << endl;
  
  s << endl;

  if (uniqueUndefNum > 0) {
    s << "// Undefined values" << endl;
    s << "const ";
    for (unsigned i=0; i<uniqueUndefNum; i++)
      s << (i > 0 ? ", " : "") << "$u." << i;
    s << ": " << getPtrType() << ";" << endl;  
    s << endl;
  }

  s << memoryModel() << endl;
  s << mallocProc() << endl;
  s << freeProc() << endl;
  s << allocaProc() << endl;
  return s.str();
}

vector<string> SmackRep::getModifies() {
  vector<string> mods;
  for (unsigned i=0; i<memoryRegions.size(); ++i)
    mods.push_back(memReg(i));
  return mods;
}

void SmackRep::addStaticInit(const llvm::Value* v) {
  using namespace llvm;
  if (const GlobalVariable* g = dyn_cast<const GlobalVariable>(v)) {
    
    if (g->hasInitializer()) {
      const Constant* init = g->getInitializer();

      if (isInt(init))
        staticInits.push_back(Stmt::assign(mem(g),expr(init)));

      else if (init->getType()->isArrayTy()) {
        ArrayType* t = (ArrayType*) init->getType();
        extraDecls.push_back(Decl::axiom(Expr::eq(
          Expr::fn("$size",Expr::id(id(g))),lit(t->getNumElements()))));
      }

      else if (init->getType()->isStructTy()) {
        StructType* t = (StructType*) init->getType();
        for (unsigned i = 0, e = t->getNumElements(); i != e; ++i) {
          Constant* c = init->getAggregateElement(i);
          assert(isInt(c));
          staticInits.push_back(Stmt::assign(Expr::sel(
              Expr::id(memReg(getRegion(g))), pa(expr(g), 1, fieldOffset(t, i))),expr(c)));
        }
      }
    }
  }
}

bool SmackRep::hasStaticInits() {
  return staticInits.size() > 0;
}

Procedure* SmackRep::getStaticInit() {
  Procedure* proc = new Procedure(STATIC_INIT);
  Block* b = new Block();
  for (unsigned i=0; i<staticInits.size(); i++)
    b->addStmt(staticInits[i]);
  b->addStmt(Stmt::return_());
  proc->addBlock(b);
  return proc;
}

vector<const Decl*> SmackRep::getExtraDecls() {
  return extraDecls;
}

} // namespace smack

