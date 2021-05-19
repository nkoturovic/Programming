
main = getLine >>= putStrLn 
main1 = getLine >>= (\line -> putStrLn ("Hello " ++ line ++ "!"))

main2 = do
    line <- getLine
    putStrLn $ "Hello " ++ line ++ "!"


maybeVal :: Maybe Int
maybeVal = Just 5 >>= (\x -> Just $ x + 5) 
maybeVal1 = return 5 >>= (\x -> Just $ x + 5) 

input message = putStrLn message >> getLine

main3 = do { x <- input "Enter question: "
           ; do { y <- input x
                ; putStrLn y
                }
           }
