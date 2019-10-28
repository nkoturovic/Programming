module Main where

import Fraction

main :: IO ()
main = do
    putStrLn "Hello world"
    putStrLn $ maybeShow (8 !-! 10)
    putStrLn $ maybeShow (1 !-! 0)
