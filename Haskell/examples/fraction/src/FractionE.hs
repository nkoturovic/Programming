module FractionE
    ( Fraction
    --, Fraction ((:-:))
    , toFraction
    , (!-!)
    , fromPair, toPair
    , num, den
    ) where

import Control.Exception
import Data.Typeable

data Fraction = Int :-: Int
              deriving (Eq)

------------ Ecception ------------
data FractionException 
  = FractionZeroDenominator
  deriving (Show,Typeable)

instance Exception FractionException
-----------------------------------
toFraction :: Int -> Int -> Fraction
toFraction n d =  
    case d of
        0 -> throw FractionZeroDenominator
        _ -> simplify (n :-: d)

(!-!) :: Int -> Int -> Fraction
(!-!) = toFraction

fromPair :: (Int, Int) -> Fraction
fromPair (x, y) = toFraction x y 

toPair :: Fraction -> (Int, Int)
toPair (n :-: d) = (n, d)

num :: Fraction -> Int
num (n :-: _) = n

den :: Fraction -> Int
den (_ :-: d) = d

simplify :: Fraction -> Fraction
simplify (n :-: d) = 
    (n `div` c) :-: (d `div` c) where c = gcd n d

showFraction :: Fraction -> String
showFraction (n :-: d) = show n ++ "/" ++ show d

instance Show Fraction where
    show = showFraction
