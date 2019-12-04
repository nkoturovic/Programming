module Main where

import MyList

main :: IO ()
main = do
    let xs = 1 :-> 2 :-> 3 :-> II
    print xs
    print $ foldl (+) 0 xs  
    print $ fmap (*2) xs 
