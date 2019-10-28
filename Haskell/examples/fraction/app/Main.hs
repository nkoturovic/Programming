module Main where

import FractionE

dbl :: Fraction -> Fraction
dbl f = (2 * (num f)) !-! den f

main :: IO ()
main = do
    putStrLn "Hello world"
    print (toFraction 2 20)
    print (fromPair (3, 9))
    let fr = 8 !-! 16
    print (dbl fr)
    print (8!-!10 == 4!-!5)
    print (8!-!10)
    print (1!-!0)
