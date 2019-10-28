module Fraction
    ( Fraction
    --, Fraction ((:-:))
    , toFraction
    , (!-!)
    , fromPair, toPair
    , num, den
    ) where

import Control.Exception
import Data.Typeable

data Fraction = Integer :-: Integer
              deriving (Eq, Ord)

------------ Ecception ------------
data FractionException 
  = FractionZeroDenominator
  deriving (Show,Typeable)

instance Exception FractionException
-----------------------------------
toFraction :: Integer -> Integer -> Fraction
toFraction n d =  
    case d of
        0 -> throw FractionZeroDenominator
        _ -> simplify (n :-: d)

infix 7 !-!
(!-!) :: Integer -> Integer -> Fraction
(!-!) = toFraction

fromPair :: (Integer, Integer) -> Fraction
fromPair (x, y) = toFraction x y 

toPair :: Fraction -> (Integer, Integer)
toPair (n :-: d) = (n, d)

num :: Fraction -> Integer
num (n :-: _) = n

den :: Fraction -> Integer
den (_ :-: d) = d

simplify :: Fraction -> Fraction
simplify (n :-: d) = 
    (n `div` c) :-: (d `div` c) where c = gcd n d

showFraction :: Fraction -> String
showFraction (n :-: d) = show n ++ "/" ++ show d

instance Show Fraction where
    show = showFraction

instance Num Fraction where
    (n1 :-: d1) + (n2 :-: d2) = ((n1 * d2) + (n2 * d1)) !-! (d1 * d2)
    (n1 :-: d1) - (n2 :-: d2) = ((n1 * d2) - (n2 * d1)) !-! (d1 * d2)
    (n1 :-: d1) * (n2 :-: d2) = (n1 * n2) !-! (d1 * d2)
    fromInteger i = i !-! 1
    abs (n :-: d) = abs n !-! abs d
    signum (n :-: d) = (signum n * signum d) !-! 1
