-- Haskell examples

f1 = putStr "Hello " >> 
	putStrLn "world"

-- Do monad
f2 = do print "Hello world"
	putStrLn "Hello world"
