data MyTuple = Simple Char Float Float | Combined Char MyTuple MyTuple | LeftT Char Float MyTuple | RightT Char MyTuple Float

expr :: MyTuple -> Float
expr (Simple '+' op1 op2) = op1 + op2
expr (Simple '-' op1 op2) = op1 - op2
expr (Simple '*' op1 op2) = op1 * op2
expr (Simple '/' op1 op2) = op1 / op2
expr (Combined '+' op1 op2) = expr(op1) + expr(op2)
expr (Combined '-' op1 op2) = expr(op1) - expr(op2)
expr (Combined '*' op1 op2) = expr(op1) * expr(op2)
expr (Combined '/' op1 op2) = expr(op1) / expr(op2)
expr (LeftT '+' op1 op2) = op1 + expr(op2)
expr (LeftT '-' op1 op2) = op1 - expr(op2)
expr (LeftT '*' op1 op2) = op1 * expr(op2)
expr (LeftT '/' op1 op2) = op1 / expr(op2)
expr (RightT '+' op1 op2) = expr(op1) + op2
expr (RightT '-' op1 op2) = expr(op1) - op2
expr (RightT '*' op1 op2) = expr(op1) * op2
expr (RightT '/' op1 op2) = expr(op1) / op2

--expr :: [String] -> Float
--expr (head:[]) = strToFloat(head)
--expr ("+": h1: h2: []) = expr([h1]) + expr([h2])
--expr ("+": h1: h2: []) = expr(concat([h1])) + expr([h2])
--expr ("-": h1: h2: []) = expr([h1]) - expr([h2])
--expr ("*": h1: h2: []) = expr([h1]) * expr([h2])
--expr ("/": h1: h2: []) = expr([h1]) / expr([h2])
--expr ("+": [(h1)]: [(h2)]: []) = expr([h1]) + expr([h2])
--expr ("-": h1: h2: []) = expr([h1]) - expr([h2])
--expr ("*": h1: h2: []) = expr([h1]) * expr([h2])
--expr ("/": h1: h2: []) = expr([h1]) / expr([h2])

--expr num = num
main :: IO ()
main = putStrLn(show(expr(Combined '/' (Simple '*' 6 12) (Simple '-' 4 6))))
--main = putStrLn(show(expr(["+", "30", ["-", "5", "6"]])))
