/**
  * Hipster cellular automaton language.
  * Type checker for the Hipster language.
  *
  * © 2017, Dominic Verity, Macquarie University, All rights reserved.
  *
  * This Source Code Form is subject to the terms of the Mozilla Public
  * License, v. 2.0. If a copy of the MPL was not distributed with this
  * file, You can obtain one at http://mozilla.org/MPL/2.0/.
  */

package compiler

import org.bitbucket.inkytonik.kiama.attribution.Attribution

/**
  * Attribute definitions of the Hipster type checker.
  */
trait TypeAnalysis extends Attribution {

  self : NameAnalysis =>

  import TypeAnalysis._
  import HipsterTree._
  import SymbolTable._
  import ConstEval._

  def tree : HipsterTree

  /**
    * Flag to mark those expressions that are constant and can be
    * evaluated at compile time.
    */
  val isConst : Expression => Boolean =
    attr {
      case IdnExpr(i) =>
        entity(i) match {
          case _ : Constant => true
          case _ : Neighbour => true
          case _ => false
        }

      // State fields are always non-constant. Assumes correctness of
      // uses of the ':' operator which is checked elsewhere.
      case NeighbourExpr(_, _) => false

      case _ : IntExpr => true
      case _ : FloatExpr => true
      case _ : BoolExpr => true
      case e : UnaryExpression => isConst(e.exp)
      case e : BinaryExpression => isConst(e.left) && isConst(e.right)

      // Note that function calls are caught by the following default
      // case and so are never regarded as constant. This is the
      // conservative thing to do in the presence of functions that may
      // have side effects.
      case _ => false
    }

  /**
    * Compute the value of a constant expression. Only needs to be
    * valid if `isConst` is true.
    */
  val value : Expression => ConstVal =
    attr {
      case IntExpr(i) => IntVal(i)
      case FloatExpr(v) => FloatVal(v)
      case TrueExpr() => BoolVal(true)
      case FalseExpr() => BoolVal(false)

      case IdnExpr(i) =>
        entity(i) match {
          case Constant(_, e) => value(e)
          case Neighbour(c) => c
          case _ => UnknownVal()
        }

      case PlusExpr(l, r) => plus(value(l), value(r))
      case MinusExpr(l, r) => minus(value(l), value(r))
      case MultExpr(l, r) => mult(value(l), value(r))
      case DivExpr(l, r) => div(value(l), value(r))
      case ModExpr(l, r) => mod(value(l), value(r))
      case NegExpr(n) => neg(value(n))
      case AndExpr(l, r) => and(value(l), value(r))
      case OrExpr(l, r) => or(value(l), value(r))
      case NotExpr(n) => not(value(n))
      case EqualExpr(l, r) => equal(value(l), value(r))
      case LessExpr(l, r) => less(value(l), value(r))
      case GreaterExpr(l, r) => greater(value(l), value(r))
      case LessEqExpr(l, r) => lesseq(value(l), value(r))
      case GreaterEqExpr(l, r) => greatereq(value(l), value(r))

      case _ => UnknownVal()
    }

  /**
    * The type of an expression.
    */
  val tipe : Expression => Type =
    attr {
      // The type of an identifier expression .
      case IdnExpr(i) =>
        entity(i) match {
          // It is an error for the name of a function or built-in to
          // be used in an identifier expression. Such errors are reported
          // elsewhere, so return `unknown` type here to avoid further
          // spurious and unhelpful type errors.
          case e : Applicable => UnknownType()
          // For all other identifiers the type of identifier expression
          // is the declared type of that identifier.
          case e : TypedEntity => e.tipe
          // Default case, we should never get here, but just in case
          // make the default `unknown`.
          case _ => UnknownType()
        }

      // Types of manifest constant expressions.
      case _ : IntExpr => IntType()
      case _ : FloatExpr => FloatType()
      case _ : BoolExpr => BoolType()

      // type inference cases for all other expression
      // node types here.

      case p : UnaryExpression =>
        p match{
          case _ : ArithmeticOp => // (-) - NegExpr
            tipe(p.exp) match{
              case IntType() => IntType()
              case FloatType() => FloatType()
              case _ => UnknownType()
            }
          case _ : BooleanOp => // (!) - NotExpr
            tipe(p.exp) match{
              case IntType() => IntType()
              case FloatType() => FloatType()
              case _ => UnknownType()
            }
          case _ => UnknownType()
        }

      case EqualExpr(l, r) => // (==)
        tipe(l) match{
          case NeighbourType() =>
            tipe(r) match{
              case NeighbourType() => BoolType()
              case _ => UnknownType()
            }
          case BoolType() =>
            tipe(r) match{
              case BoolType() => BoolType()
              case _ => UnknownType()
            }
          case IntType() =>
            tipe(r) match{
              case IntType() => BoolType()
              case FloatType() => BoolType()
              case _ => UnknownType()
            }
          case FloatType() =>
            tipe(r) match{
              case IntType() => BoolType()
              case FloatType() => BoolType()
              case _ => UnknownType()
            }
          case _ => UnknownType()
        }

      case p : BinaryExpression =>
        p match{
          case _ : ArithmeticOp => // (+, -, *, /, % etc.)
            tipe(p.left) match{
              case IntType() =>
                tipe(p.right) match{
                  case IntType() => IntType()
                  case FloatType() => FloatType()
                  case _ => UnknownType()
                }
              case FloatType() =>
                tipe(p.right) match{ // Always return float since first type is float
                  case IntType() => FloatType()
                  case FloatType() => FloatType()
                  case _ => UnknownType()
                }
              case _ => UnknownType()
            }
          case _ : BooleanOp => // (||, &&)
            tipe(p.left) match{
              case BoolType() =>
                tipe(p.right) match{
                  case BoolType() => BoolType()
                  case _ => UnknownType()
                }
              case _ => UnknownType()
            }
          case _ : RelationalOp => // (<, >, <=, or =>)
            tipe(p.left) match{
              case BoolType() =>
                tipe(p.right) match{
                  case BoolType() => BoolType()
                  case _ => UnknownType()
                }
              case IntType() =>
                tipe(p.right) match{
                  case IntType() => BoolType()
                  case FloatType() => BoolType()
                  case _ => UnknownType()
                }
              case FloatType() =>
                tipe(p.right) match{
                  case IntType() => BoolType()
                  case FloatType() => BoolType()
                  case _ => UnknownType()
                }
              case _ => UnknownType()
            }
          case _ => UnknownType()
        }

      case NeighbourExpr(nbr, fld) =>
        entity(fld) match{
          case e : TypedEntity => e.tipe
          case _ => UnknownType()
        }

      case FunCallExpr(idn, args) =>
        entity(idn) match{
          case e : Applicable =>
            e match {
              case function : Function => function.tipe
              case builtin : BuiltIn => builtin.tipe
              case _ => UnknownType()
            }
          case _ => UnknownType()
        }

      // We shouldn't get here, but if all else fails report that the type
      // of this expression is `unknown`.
      case _ => UnknownType()
    }

  /**
    * The set of expected types of an expression, as imposed
    * by the context of that expression.
    */
  val expTipe : Expression => Set[Type] =
    attr {
      // Expected types of dimension expressions.
      case tree.parent(_ : BoundedDim) => Set(IntType())
      case tree.parent(_ : CyclicDim) => Set(IntType())

      // The expected type of an initialiser expression in a
      // variable or constant declaration must be compratible
      // with the declared type of that identifier.
      case tree.parent.pair(n, ConstantDecl(t,_,_)) =>
        compatTypes(t)
      case tree.parent.pair(n, VarDecl(t,_,_)) =>
        compatTypes(t)

      // FIXME: Add cases to compute the set of expected types for an
      // expression node by inspecting the type of its parent.

      // Assignment statement. The lvalue can have any non-void type
      // and the rvalue must have a type compatible with the type of
      // the lvalue.
      case tree.parent.pair(n, AssignStmt(lval, exp)) if n eq exp =>
        compatTypes(tipe(lval))

      // If statement. The control expression must be of type `bool`.
      case tree.parent.pair(n, IfStmt(exp, thn, els)) if n eq exp =>
        Set(BoolType())

      // For statement, The from, to and step expressions must all be
      // of type `int`.
      case tree.parent.pair(n : Expression, p : ForStmt) =>
        Set(IntType())

      // Function call statement. The return type of a function called
      // as a statement can be any of the builtin types. Any returned
      // value is discarded.
      case tree.parent.pair(n, FunCallStmt(fcall)) if n eq fcall =>
        Set(IntType(), FloatType(), BoolType(), NeighbourType())

      // Return statement. The return expression type must be compatible
      // with the return type of the enclosing function or colour
      // mapper.
      case tree.parent(p : ReturnStmt) =>
        compatTypes(returnTipe(p))

      // Arithmetic operations expect their arguments to be of integer,
      // floating point or boolean type. // boolean type???
      case tree.parent(p : ArithmeticOp) =>
        Set(IntType(), FloatType())

      // Boolean operations expect arguments of boolean type.
      case tree.parent(p : BooleanOp) =>
        Set(BoolType())

      // An equals expression can compare integers, floats, booleans
      // and neighbours...
      case tree.parent.pair(n, EqualExpr(l, _)) if n eq l =>
        Set(IntType(), FloatType(), BoolType(), NeighbourType())

      // ...and the type of the right hand argument of an equals must be
      // compatible with that of its left hand argument...
      case tree.parent.pair(n, EqualExpr(l,r)) if n eq r =>
        tipe(l) match {
          case IntType() | FloatType() => Set(IntType(),FloatType())
          case t => Set(t)
        }

      // ... any other relational expression can only compare integers
      // and floats.
      case tree.parent.pair(n, p : RelationalOp) if n eq p =>
        Set(IntType(), FloatType())

      // The expected types of the arguments in a function call should
      // be compatible with the declared types, which are distributed
      // through the `paramTipe` attribute. If there are more arguments
      // than parameters the extra arguments can have any type compatible
      // with `unknown`.
      case tree.parent.pair(p : Expression, r : FunCallExpr) =>
        if (paramTipe(p).nonEmpty){
          compatTypes(paramTipe(p).head)
        }
        else{
          compatTypes(UnknownType())
        }

      // A neighbour state field expression expects its left operand
      // to be of `neighbour` type.
      case tree.parent.pair(n, NeighbourExpr(nbr, fld)) if n eq nbr =>
        Set(NeighbourType())

      // A coordinate expression expects its ordinates to be integers.
      case tree.parent(p : CoordExpr) =>
        Set(IntType())

      // A subset clause in an `iterate...over` statement must have
      // entries of `neighbour` type.
      case tree.parent.pair(e : Expression, p : NeighbourSet) =>
        Set(NeighbourType())

      // We shouldn't get here, but just in case the default is compatible
      // with the computed expression type.
      case n => compatTypes(tipe(n))
    }

  /**
    * An attribute to distribute the declared types of the parameters
    * of a function across the arguments of a call to that function.
    * If an expression is an argument in such a call, the first
    * entry of this vector is the expected type of that parameter.
    *
    * In cases where the call has more arguments than there are
    * declared parameters, this attributes the empty vector to any
    * extra arguments.
    */
  val paramTipe : Expression => Vector[Type] =
    attr {
      case tree.parent.pair(n, p : FunCallExpr) =>
        n match {
          case tree.prev(l : IdnUse) =>
            entity(l) match {
              case e : Applicable => e.paramTipes
              case _ => Vector()
            }
          case tree.prev(l : Expression) =>
            paramTipe(l) match {
              case _ +: ts => ts
              case ts @ Vector() => ts
            }
          case _ => Vector()
        }
      case _ => Vector()
    }

  /**
    * The return type of the current code block. Is either
    *   * the return type in a function declaration which has one, or
    *   * `int` if we are in a mapper declaration, or
    * Is unknown type otherwise.
    */
  val returnTipe : Statement => Type =
    attr {
      case tree.parent(_ : ColourMapperDecl) => IntType()

      case tree.parent(FunctionDecl(_, _, r, _)) =>
        r getOrElse(UnknownType())

      case tree.parent(p : Statement) =>
        returnTipe(p)

      case _ => UnknownType()
    }
}

/**
  * Companion object for the Hipster type checker.
  */
object TypeAnalysis {

  import HipsterTree._

  /**
    * Returns the set of types compatible with a given type.
    */
  def compatTypes(t : Type) : Set[Type] =
    t match {
      case FloatType() => Set(IntType(), FloatType())
      case UnknownType() =>
        Set(IntType(), FloatType(), NeighbourType(),
          BoolType())
      case _ => Set(t)
    }

}
