#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include <vector>

using namespace llvm;

namespace {
struct SimpleVectorizer : public FunctionPass {
  static char ID;
  static const int VectorWidth = 4;

  LoopInfo *LI;
  ScalarEvolution *SE;

  // The set of loops we want to vectorize.
  std::vector<Loop *> LoopsToVectorize;

  // A map that contains for each original value the corresponding new
  // scalarized value for a given scalar iteration.
  std::map<std::pair<int, Value *>, Value *> ValueMap;

  // A map that contains for each original value the corresponding new
  // vector value.
  std::map<Value *, Value *> VectorMap;

  SimpleVectorizer() : FunctionPass(ID) {}

  // Return true if the loop is innermost.
  bool isInnermostLoop(Loop *L);

  // Return true if we are capable of vectorizing the loop.
  bool isValidLoop(Loop *L);

  // Collect loops that can be vectorized.
  void collectLoops(Function &F);

  // Print loops that should be vectorized.
  void printLoops(Function &F);

  // Transform the loops that should be vectorized.
  void transformLoops();

  // Transform the Loop *L
  void transformLoop(Loop *L);

  // Return the single basic block that represents the body of @p L.
  BasicBlock *getSingleBodyBlock(Loop *L);

  // Check if the loop structure of @p L is simple (canonical).
  bool isSimpleLoopStructure(Loop *L);

  // Get the new value for a given original value in the scalar lane @p Lane.
  Value *getNewValue(int Lane, Value *V);

  // Get the PHI node which serves as induction variable for @p L.
  Value *getIndVar(Loop *L);

  // Check if the loop body of @p L only contains instructions we can vectorize.
  bool isValidBody(Loop *L);

  // Get a scalar evolution expression that represents the memory access
  // location of @p Inst.
  const SCEV *getPointerSCEV(Instruction *Inst);

  // Get the size of the elements (in bytes) loaded or stored by Inst.
  size_t getElementSize(Instruction *Inst);

  // Check if an instruction @p Inst has stride one access in loop @p L.
  bool isStrideOneAccess(Instruction *Inst, Loop *L);

  virtual bool runOnFunction(Function &F) {
    LoopsToVectorize.clear();
    ValueMap.clear();

    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();

    errs() << "I saw a function called " << F.getName() << "!\n";

    collectLoops(F);
    printLoops(F);
    transformLoops();

    return false;
  }

  void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequired<LoopInfoWrapperPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
  }
};

bool SimpleVectorizer::isInnermostLoop(Loop *L) {
}

bool SimpleVectorizer::isValidLoop(Loop *L) {
}

const SCEV *SimpleVectorizer::getPointerSCEV(Instruction *Inst) {
}

size_t SimpleVectorizer::getElementSize(Instruction *Inst) {
}

bool SimpleVectorizer::isStrideOneAccess(Instruction *Inst, Loop *L) {
}

void SimpleVectorizer::collectLoops(Function &F) {
}

void SimpleVectorizer::printLoops(Function &F) {
}

void SimpleVectorizer::transformLoops() {
}

BasicBlock *SimpleVectorizer::getSingleBodyBlock(Loop *L) {
}

bool SimpleVectorizer::isValidBody(Loop *L) {
}

bool SimpleVectorizer::isSimpleLoopStructure(Loop *L) {
}

Value *SimpleVectorizer::getNewValue(int Lane, Value *V) {
}

Value *SimpleVectorizer::getIndVar(Loop *L) {
}

void SimpleVectorizer::transformLoop(Loop *L) {
}
} // namespace

char SimpleVectorizer::ID = 0;

namespace llvm {
void initializeSimpleVectorizerPass(llvm::PassRegistry &);
}

class StaticInitializer {
public:
  StaticInitializer() {
    llvm::PassRegistry &Registry = *llvm::PassRegistry::getPassRegistry();
    llvm::initializeSimpleVectorizerPass(Registry);
  }
};

static StaticInitializer InitializeEverything;

INITIALIZE_PASS_BEGIN(SimpleVectorizer, "simple-vectorizer",
                      "Simple Vectorizer", false, false);
INITIALIZE_PASS_DEPENDENCY(LoopInfoWrapperPass);
INITIALIZE_PASS_DEPENDENCY(ScalarEvolutionWrapperPass);
INITIALIZE_PASS_END(SimpleVectorizer, "simple-vectorizer", "Simple Vectorizer",
                    false, false)
