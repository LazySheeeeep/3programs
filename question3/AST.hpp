#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>

using namespace std;

class ASTNode {
public:
  ASTNode() = default;
  virtual ~ASTNode() = default;
};

class IdNode : public ASTNode {
private:
  const string id__;

public:
  IdNode(const string &id) : id__(id) {}

  string id() const { return id__; }
};

class BinaryNode : public ASTNode {
protected:
  unique_ptr<ASTNode> left_;
  unique_ptr<ASTNode> right_;

public:
  BinaryNode(ASTNode *left, ASTNode *right)
      : left_(unique_ptr<ASTNode>(left)), right_(unique_ptr<ASTNode>(right)) {}

  virtual ~BinaryNode() = default;

  ASTNode *left() const { return left_.get(); }
  ASTNode *right() const { return right_.get(); }
};

class OrNode : public BinaryNode {
public:
  OrNode(ASTNode *left, ASTNode *right) : BinaryNode(left, right) {}
};

class AndNode : public BinaryNode {
public:
  AndNode(ASTNode *left, ASTNode *right) : BinaryNode(left, right) {}
};

class EqualsNode : public BinaryNode {
private:
  bool isEqual_;

public:
  EqualsNode(ASTNode *left, ASTNode *right, bool isEqual)
      : BinaryNode(left, right), isEqual_(isEqual) {}

  bool isEqual() const { return isEqual_; }
};

#endif // AST_HPP
#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>

using namespace std;

class ASTNode {
public:
  ASTNode() = default;
  virtual ~ASTNode() = default;
};

class IdNode : public ASTNode {
private:
  const string id__;

public:
  IdNode(const string &id) : id__(id) {}

  string id() const { return id__; }
};

class BinaryNode : public ASTNode {
protected:
  ASTNode *left_;
  ASTNode *right_;

public:
  BinaryNode(ASTNode *left, ASTNode *right) : left_(left), right_(right) {}

  virtual ~BinaryNode() {
    delete left_;
    delete right_;
  }

  ASTNode *left() const { return left_; }
  ASTNode *right() const { return right_; }
};

class OrNode : public BinaryNode {
public:
  OrNode(ASTNode *left, ASTNode *right) : BinaryNode(left, right) {}
};

class AndNode : public BinaryNode {
public:
  AndNode(ASTNode *left, ASTNode *right) : BinaryNode(left, right) {}
};

class EqualsNode : public BinaryNode {
private:
  bool isEqual_;

public:
  EqualsNode(ASTNode *left, ASTNode *right, bool isEqual)
      : BinaryNode(left, right), isEqual_(isEqual) {}

  bool isEqual() const { return isEqual_; }
};

#endif // AST_HPP
