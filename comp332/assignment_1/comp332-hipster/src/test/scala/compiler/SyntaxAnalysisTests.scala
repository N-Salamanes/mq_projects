/**
  * Hipster cellular automaton language.
  * Tests of the Hipster parser.
  *
  * © 2017, Dominic Verity, Macquarie University, All rights reserved.
  * 
  * This Source Code Form is subject to the terms of the Mozilla Public
  * License, v. 2.0. If a copy of the MPL was not distributed with this
  * file, You can obtain one at http://mozilla.org/MPL/2.0/.
  */

package org.bitbucket.dominicverity.hipster
package compiler

import org.bitbucket.inkytonik.kiama.util.ParseTests
import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

/**
 * Tests that check that the parser works correctly.  I.e., it accepts correct
 * input and produces the appropriate trees, and it rejects illegal input.
 */
@RunWith(classOf[JUnitRunner])
class SyntaxAnalysisTests extends ParseTests {

  import HipsterTree._

  val parsers = new SyntaxAnalysis (positions)
  import parsers._

  // Tests of numerical constant parsing.

  test("parsing decimal constant as a factor") {
    factor("34570") should
      parseTo[Expression] (IntExpr(34570))
  }

  test("parsing a hexadecimal constant as a factor") {
    factor("0xfffe") should
      parseTo[Expression] (IntExpr(65534))
  }

  test("parsing a binary constant as a factor") {
    factor("0B0101001") should
      parseTo[Expression] (IntExpr(41))
  }

  test("parsing an octal constant as a factor") {
    factor("0o777") should
      parseTo[Expression] (IntExpr(511))
  }

  test("parsing a float constant as a factor") {
    factor("10.22") should
      parseTo[Expression] (FloatExpr(10.22))
  }

  test("parsing a float constant with exponent as a factor") {
    factor("21e-5") should
      parseTo[Expression] (FloatExpr(0.00021))
  }

  test("parsing a float with exponent as a factor") {
    factor("0.123E6") should
      parseTo[Expression] (FloatExpr(123000))
  }

  // Negative constants.
  test("parsing a negative hexadecimal constant as a factor") {
    factor("-0x56") should
      parseTo[Expression] (NegExpr(IntExpr(86)))
  }

  test("parsing a negative float constant as a factor") {
    factor("-0.123e3") should
      parseTo[Expression] (NegExpr(FloatExpr(123)))
  }

  test("parsing a doubly negated constant as a factor") {
    factor("--20") should
      parseTo[Expression] (NegExpr(NegExpr(IntExpr(20))))
  }

  // A few tests of attempts to parse incorrect numeric constants.
  test("parsing a non-number as a integer constant gives an error") {
    intExpr("hello") should
      failParseAt(1, 1, "integer constant expected")
  }

  // A few tests of attempts to parse incorrect numeric constants.
  test("parsing a non-number as a floating point constant gives an error") {
    floatExpr("hello") should
      failParseAt(1, 1, "floating point constant expected")
  }

  test("parsing an overflowing integer constant gives an error") {
    factor("9999999999999999999") should
      failParseAt(1, 1, "integer will not fit into 32 bits")
  }

  test("parsing an overflowing floating point constant gives an error") {
    factor("1.56e27809") should
      failParseAt(1, 1, "floating point number is infinite")
  }

  test("parsing a very small floating point constant gives 0") {
    factor("1.56e-27809") should
      parseTo[Expression] (FloatExpr(0.0))
  }

  // Parsing identifiers
  test("parsing an identifier as a factor") {
    factor("doms_ident") should
      parseTo[Expression] (IdnExpr(IdnUse("doms_ident")))
  }

  test("parsing an identifier containing numerals") {
    factor("doms0_ident22") should
      parseTo[Expression] (IdnExpr(IdnUse("doms0_ident22")))
  }

  test("parsing a keyword as an identifier should fail") {
    factor("updater") should
      failParseAt(1, 1, "reserved word found where identifier expected")
  }

  test("parsing another keyword as an identifier should fail") {
    factor("then") should
      failParseAt(1, 1, "reserved word found where identifier expected")
  }

  test("parsing an identifier starting with a keyword is ok") {
    factor("function0") should
      parseTo[Expression] (IdnExpr(IdnUse("function0")))
  }

  // Parsing function calls and neighbour state expressions.
  test("parsing a neighbour expression as a factor") {
    factor("NE:height") should
      parseTo[Expression] (NeighbourExpr(IdnUse("NE"),IdnUse("height")))
  }

  test("parsing a neighbour expression containing a keyword should fail") {
    factor("NE:state") should
      failParseAt(1, 4, "reserved word found where identifier expected")
  }

  test("parsing a neighbour exprssion containing a keyword should fail (2)") {
    factor("if:size") should
      failParseAt(1, 1, "reserved word found where identifier expected")
  }

  test("parsing a neighbour expr containing a non-identifier should fail") {
    phrase(factor)("NE:10ten") should
      failParseAt(1, 4, "identifier expected")
  }

  test("parsing a neighbour expr containing a non-identifier should fail (2)") {
    phrase(factor)("10:ten") should
      failParseAt(1, 3, "end of input expected")
  }

  test("parsing a function call as a factor") {
    factor("my_function(10,dom)") should
      parseTo[Expression] (FunCallExpr(IdnUse("my_function"),
        Vector(IntExpr(10),IdnExpr(IdnUse("dom")))))
  }

  test("parsing another function call as a factor") {
    factor("your_function(10+hello,goodbye)") should
      parseTo[Expression] (FunCallExpr(
        IdnUse("your_function"),
        Vector(
          PlusExpr(
            IntExpr(10),
            IdnExpr(IdnUse("hello"))),
          IdnExpr(IdnUse("goodbye")))))
  }

  test("parsing a simple arithmetic expression, checking precedence rules") {
    expression("2 + 3 * 4") should
    parseTo[Expression](
      PlusExpr(
        IntExpr(2),
        MultExpr(
          IntExpr(3),
          IntExpr(4))))
  }

  test("parsing a potentially ambiguous dangling else statement") {
    statement("if test then if test2 then count = 0; else count = 1;") should
      parseTo[Statement] (
        IfStmt(
          IdnExpr(IdnUse("test")),
          IfStmt(
            IdnExpr(IdnUse("test2")),
            AssignStmt(IdnExpr(IdnUse("count")),IntExpr(0)),
            Some(AssignStmt(IdnExpr(IdnUse("count")),IntExpr(1)))),
          None))
  }

  test("use a block statement to attach the else to the outer if"){
    statement(
      "if test then { if test2 then count = 0; } else count = 1;") should
      parseTo[Statement] (
        IfStmt(
          IdnExpr(IdnUse("test")),
          Block(
            Vector(
              IfStmt(
                IdnExpr(IdnUse("test2")),
                AssignStmt(IdnExpr(IdnUse("count")),IntExpr(0)),
                None))),
          Some(AssignStmt(IdnExpr(IdnUse("count")),IntExpr(1)))))
  }

  // FIXME add tests of your parsers here.
  /**
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    *   coordExpr tests
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    */

  test("parsing a coordinate expression with vector expression") {
    coordExpr("[1,1]") should
      parseTo[Expression](
        CoordExpr(Vector(IntExpr(1), IntExpr(1)))
      )
  }

  test("parsing a coordinate expression with a negative vector expression") {
    coordExpr("[-1,1]") should
      parseTo[Expression](
        CoordExpr(Vector(NegExpr(IntExpr(1)), IntExpr(1)))
      )
  }

  test("parsing a coordinate expression with an exponent vector expression") {
    coordExpr("[2e2,1]") should
      parseTo[Expression](
        CoordExpr(Vector(FloatExpr(200), IntExpr(1)))
      )
  }

  test("parsing a coordinate expression with a decimal vector expression") {
    coordExpr("[5.7,1]") should
      parseTo[Expression](
        CoordExpr(Vector(FloatExpr(5.7), IntExpr(1)))
      )
  }

  test("parsing a coordinate expression with an incomplete vector expression") {
    coordExpr("[,1]") should
      failParseAt(1, 2, "identifier or numerical constant expected")
  }

  /**
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    *   expression2,3,4 tests
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    */
  test("parsing an expression with a equal relational operator 1") {
    expression("5==5") should
      parseTo[Expression](
        EqualExpr(IntExpr(5),IntExpr(5))
      )
  }

  test("parsing an expression with a equal relational operator 2") {
    expression("hi==hi") should
      parseTo[Expression](
        EqualExpr(IdnExpr(IdnUse("hi")),IdnExpr(IdnUse("hi")))
      )
  }

  /**
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    *   cellStmt tests
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    */
  test("parsing a cell with coordinates with an if statement"){
    cellStmt("cell [2,5] if alive == true then alive = false;") should
      parseTo[Statement](
        CellStmt(CoordExpr(Vector(IntExpr(2), IntExpr(5))),
          IfStmt(EqualExpr(IdnExpr(IdnUse("alive")),TrueExpr()),
            AssignStmt(IdnExpr(IdnUse("alive")),FalseExpr()),
            None)
        )
      )
  }

  test("parsing a cell with coordinates with an invalid if statement"){
    cellStmt("cell [2,5] if alive = true then alive = false;") should
      failParseAt(1,21, "'then' expected but '=' found")
  }

  test("parsing a cell with coordinates with no statement"){
    cellStmt("cell [2,5] ;") should
      parseTo[Statement](
        CellStmt(CoordExpr(Vector(IntExpr(2), IntExpr(5))), EmptyStmt())
      )
  }

  test("parsing a cell with coordinates with no statement and no semicolon"){
    cellStmt("cell [2,5]") should
      failParseAt(1,11, "';' expected but end of source found")
  }

  test("parsing a cell with coordinates with a statement and no semicolon"){
    cellStmt("cell [2,5] if alive == true then alive = false") should
      failParseAt(1,47, "';' expected but end of source found")
  }

  /**
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    *   forStmt tests
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    */

  test("parsing a valid for statement"){
    forStmt("for i = 0 to 5 test=1;") should
      parseTo[ForStmt](
        ForStmt(IdnDef("i"),IntExpr(0),IntExpr(5),None,AssignStmt(IdnExpr(IdnUse("test")),IntExpr(1)))
      )
  }

  /**
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    *   forStmt tests
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    */
  test("parsing a valid for iterate over statement"){
    iterateOverStmt("iterate i over all test=1;") should
      parseTo[IterateOverStmt](
        IterateOverStmt(IdnDef("i"),All(),AssignStmt(IdnExpr(IdnUse("test")),IntExpr(1)))
      )
  }

  /**
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    *   neighbourSet tests
    *   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    */
  test("parsing a valid neighbourSet"){
    neighbourSet("all") should
      parseTo[NeighbourSet](
        All()
      )
  }

}
