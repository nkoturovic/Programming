-- Haskell examples
{- Prelude is standard module
 - print, putStr, putStrLn - prints to stdout 
 - You can run shell command with :!
 - :load :reload :info :type :quit
 - '->' - computation abstraction
 -}

{- Types: Bool, Char, String, Int, Integer, Float, Double -}
{- Type classes: Eq, Ord, Num, Integral, Fractional -}

isPositive' n = if n > 0 then True
              else False
            
isPositive num | num > 0 = True
               | otherwise = False;

-- return is needed because of IO monad stuff
-- '>>=' - Bind operator (similar to shell's |)
f1 n = return (isPositive n)
       >>= print
       >> putStrLn " number"

-- Do monad
-- let defines variable local to f2
f2 n = do 
    let isPos = isPositive n
    print (if isPos then "yes" else "no")
    komentar <- getLine
    print ("Vas komentar je: " ++ komentar)

f3 = do print "Hello world"
        putStrLn "Hello world"
