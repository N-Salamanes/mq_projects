/**
  * Hipster cellular automaton language.
  * Parser for Hipster source code.
  *
  * © 2017, Dominic Verity, Macquarie University, All rights reserved.
  * 
  * This Source Code Form is subject to the terms of the Mozilla Public
  * License, v. 2.0. If a copy of the MPL was not distributed with this
  * file, You can obtain one at http://mozilla.org/MPL/2.0/.
  */

package org.bitbucket.dominicverity.hipster
package compiler

import org.bitbucket.inkytonik.kiama.parsing.Parsers
import org.bitbucket.inkytonik.kiama.util.Positions

/**
  * Module containing parsers for the Hipster language.
  */
class SyntaxAnalysis (positions : Positions)
    extends Parsers (positions) with ParserExtras {

  import HipsterTree._
  import scala.language.postfixOps

  lazy val parser : PackratParser[HipsterProgram] =
    phrase (program)

  lazy val program : PackratParser[HipsterProgram] =
    (topLevelDecl+) ^^ HipsterProgram

  // Parsers for top level declarations.

  lazy val topLevelDecl : PackratParser[TopLevelDecl] =
    functionDecl | dimDecl | stateDecl | neighbourhoodDecl |
      updaterDecl | colourMapperDecl | initialiserDecl | constantDecl

  lazy val dimDecl : PackratParser[DimDecl] =
    "dimension" ~>
      "(" ~> rep1sep(expression ~ opt("cyclic"), ",") <~
      ")" <~ ";" ^^
      { lst => DimDecl(
        lst map {
          case (e ~ Some(_)) => (e,true);
          case (e ~ None) => (e,false) })}

  // [FINISHED] FIXME add a parser for the top level neighbourhood declaration here.
  lazy val neighbourhoodDecl : PackratParser[NeighbourhoodDecl] =
    "neighbourhood" ~> (rep1sep((idnDef <~ "=") ~ coordExpr, ",") <~ ";") ^^
      { lst => NeighbourhoodDecl(
        lst map {
          case (i ~ e) => (i, e);
        }
      )}

  lazy val stateDecl : PackratParser[StateDecl] =
    "state" ~> "{" ~> rep(varDecl) <~ "}" ^^ StateDecl

  lazy val constantDecl : PackratParser[ConstantDecl] =
    varDecl ^^ ConstantDecl

  lazy val updaterDecl : PackratParser[UpdaterDecl] =
    "updater" ~> "{" ~> rep(statement) <~ "}" ^^ UpdaterDecl

  lazy val initialiserDecl : PackratParser[InitialiserDecl] =
    "initialiser" ~> idnDef ~ ("{" ~> rep(statement) <~ "}") ^^
      InitialiserDecl

  lazy val colourMapperDecl : PackratParser[ColourMapperDecl] =
    "mapper" ~> "{" ~> rep(statement) <~ "}" ^^ ColourMapperDecl

  // [FINISHED] FIXME add a parser for function declarations here.
  lazy val functionDecl : PackratParser[FunctionDecl] =
    ("function" ~> idnDef <~ "(") ~ (rep1sep(tipe ~ idnDef, ",") <~ ")") ~
      opt(":" ~> tipe) ~ ("{" ~> rep(statement) <~"}") ^^
      {
        case idn ~ params ~ ret ~ stmts => FunctionDecl(idn,
          params map {
            case (t ~ i) => (t, i);
          },
          ret, stmts)
      }

  // Parsers for variable declarations.

  lazy val varDecl : PackratParser[VarDecl] =
    tipe ~ idnDef ~ opt("=" ~> expression) <~ ";" ^^ VarDecl

  lazy val tipe : PackratParser[Type] =
    "int" ^^ (_ => IntType()) |
      "boolean" ^^ (_=> BoolType()) |
      "float" ^^ (_=> FloatType()) |
      "neighbour" ^^ (_=> NeighbourType())

  // Parsers for statements

  lazy val statement : PackratParser[Statement] =
    varDecl | block | ifStmt | iterateOverStmt | forStmt |
      returnStmt | cellStmt | assignStmt | funCallStmt  | emptyStmt

  lazy val block : PackratParser[Block] =
    "{" ~> rep(statement) <~ "}" ^^ Block

  lazy val emptyStmt : PackratParser[EmptyStmt] =
    ";" ^^ (_ => EmptyStmt())

  lazy val assignStmt : PackratParser[AssignStmt] =
    (lvalue <~ "=") ~ (expression <~ ";") ^^ AssignStmt

  lazy val ifStmt : PackratParser[IfStmt] =
    ("if" ~> expression) ~ ("then" ~> statement) ~
      opt("else" ~> statement) ^^ IfStmt

  // [FINISHED] FIXME add parsers for `iterate...over` and `for` loops here.
  lazy val neighbourSet : PackratParser[NeighbourSet] =
    "all" ^^ (_ => All()) |
    "others" ^^ (_ => Others()) |
    "[" ~> rep1sep(idnUse, ",") <~ "]" ^^ Subset

  lazy val iterateOverStmt : PackratParser[IterateOverStmt] =
    ("iterate" ~> idnDef) ~ ("over" ~> neighbourSet) ~ statement ^^ IterateOverStmt

  lazy val forStmt : PackratParser[ForStmt] =
    ("for" ~> idnDef) ~ ("=" ~> expression) ~ ("to" ~> expression) ~
      opt("step" ~> expression) ~ statement ^^ ForStmt

  lazy val funCallStmt : PackratParser[FunCallStmt] =
    (idnUse <~ "(") ~ (repsep(expression, ",") <~ ")") <~
      ";" ^^ FunCallStmt

  lazy val returnStmt : PackratParser[ReturnStmt] =
    "return" ~> opt("(" ~> expression <~ ")") <~ ";" ^^ ReturnStmt

  // [FINISHED] FIXME add a parser for `cell` statements here
  lazy val cellStmt : PackratParser[CellStmt] =
    ("cell" ~> coordExpr) ~ statement ^^ CellStmt

  // Expression parsers.
  // Precidence and associativity rules implemented in the
  // time honoured fashion.

  override lazy val expression : PackratParser[Expression] =
    expression ~ ("&&" ~> expression2) ^^ AndExpr |
      expression ~ ("||" ~> expression2) ^^ OrExpr |
      expression2

  // [FINISHED] FIXME complete this expression parser.
  lazy val expression2 : PackratParser[Expression] =
	  expression2 ~ ("==" ~> expression3) ^^ EqualExpr |
      expression2 ~ ("<=" ~> expression3) ^^ LessEqExpr |
      expression2 ~ (">=" ~> expression3) ^^ GreaterEqExpr |
      expression2 ~ ("<" ~> expression3) ^^ LessExpr |
      expression2 ~ (">" ~> expression3) ^^ GreaterExpr |
      expression3

	lazy val expression3 : PackratParser[Expression] =
	  expression3 ~ ("+" ~> expression4) ^^ PlusExpr |
      expression3 ~ ("-" ~> expression4) ^^ MinusExpr |
      expression4

  lazy val expression4 : PackratParser[Expression] =
    expression4 ~ ("*" ~> factor) ^^ MultExpr |
    expression4 ~ ("/" ~> factor) ^^ DivExpr |
    expression4 ~ ("%" ~> factor) ^^ ModExpr |
      factor

  lazy val factor : PackratParser[Expression] =
    "true" ^^ (_ => TrueExpr()) |
      "false" ^^ (_ => FalseExpr()) |
      "!" ~> factor ^^ NotExpr |
      "-" ~> factor ^^ NegExpr |
      "+" ~> factor |
      "(" ~> expression <~ ")" | leaf

  // [FINISHED] FIXME add a parser for coordinate expressions here.
  lazy val coordExpr : PackratParser[CoordExpr] =
    "[" ~> rep1sep(expression, ",") <~ "]" ^^ CoordExpr
}
