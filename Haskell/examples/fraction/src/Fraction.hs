module Fraction
    ( Fract
    , Fraction
    , toFraction
    , (!-!)
    , fromPair, toPair
    , num, den
    ) where

import Control.Exception
import Data.Typeable

infixl 7 !-! 

data Fract t =  t :-: t
              deriving (Eq)

type Fraction = Fract Integer

------------ Ecception ------------
data FractionException 
  = FractionZeroDenominator
  deriving (Show,Typeable)

instance Exception FractionException
-----------------------------------
toFraction :: (Integral t, Num t, Show t) => t -> t -> Fract t
toFraction n d =  
    case d of
        0 -> throw FractionZeroDenominator
        _ -> simplify (n :-: d)

(!-!) :: (Integral t, Num t, Show t) => t -> t -> Fract t
(!-!) = toFraction

fromPair :: (Integral t, Num t, Show t) => (t, t) -> Fract t
fromPair (x, y) = toFraction x y 

toPair :: Fract t -> (t, t)
toPair (n :-: d) = (n, d)

num :: Fract t -> t
num (n :-: _) = n

den :: Fract t -> t
den (_ :-: d) = d


simplify :: (Integral t) => Fract t -> Fract t
simplify (n :-: d) = 
    (n `div` c) :-: (d `div` c) where c = gcd n d

instance (Show t) => Show (Fract t) where
    show (n :-: d) = show n ++ "/" ++ show d

instance (Show t, Integral t, Num t) => Num (Fract t) where
    (n1 :-: d1) + (n2 :-: d2) = ((n1 * d2) + (n2 * d1)) !-! (d1 * d2)
    (n1 :-: d1) - (n2 :-: d2) = ((n1 * d2) - (n2 * d1)) !-! (d1 * d2)
    (n1 :-: d1) * (n2 :-: d2) = (n1 * n2) !-! (d1 * d2)
    fromInteger i =  fromIntegral i :-: 1
    abs (n :-: d) = abs n !-! abs d
    signum (n :-: d) = (signum n * signum d) !-! 1

instance (Integral t) => Ord (Fract t)  where
    (n1 :-: d1) <= (n2 :-: d2)  =  n1 * d2 <= n2 *d1 
    (n1 :-: d1) < (n2 :-: d2)  =  n1 * d2 < n2 *d1 
