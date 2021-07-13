#include "Evaluator.h"

namespace myc {

  Evaluator::Evaluator() {}

  std::string Evaluator::get_string(std::shared_ptr<Expr> root) const {
    PrinterDispatcher dispatcher;
    return root->accept(dispatcher);
  }
  double Evaluator::compute(std::shared_ptr<Expr> root) const {
    switch (root->op) {
      case TokenType::PLUS:
        return compute(root->left) + compute(root->right);
        break;
      case TokenType::MINUS:
        if (root->right == nullptr) {
          return -1 * compute(root->left);
        }else{
          return compute(root->left) - compute(root->right);
        }
        break;
      case TokenType::MULTIPLY:
        return compute(root->left) * compute(root->right);
        break;
      case TokenType::DIVIDE:
        return compute(root->left) / compute(root->right);
        break;
      default:
        return root->number;
        break;
    }
  }

}
