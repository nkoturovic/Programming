{- Lists -}

f1 = do
    let l = [1, 2]
    print (2 : l)
    print (l !! 1)
    print ([0, 0] ++ [1, 1])
    print (take 2 [1,2,3]) -- take 2 el from list
    print (null l) -- {True if l is empty }
    print (head l) -- head of list
    print (tail l) -- tail of list
    print (zip [1,2] ["a","b"]) -- zip two lists
    print (elem 3 [1,2]) -- is elem 3 in list ?
    
{- Main must print -> IO i-}
main = do
   f1

myheadfunc :: [x] -> x
myheadfunc (x:_) = x

mytailfunc :: [x] -> [x]
mytailfunc (_:xs) = xs
