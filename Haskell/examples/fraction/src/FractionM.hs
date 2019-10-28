module FractionM
    ( Fraction
    --, Fraction ((:-:))
    , toFraction
    , (!-!)
    , fromPair, toPair
    , num, den
    , maybeShow
    ) where

data Fraction = Int :-: Int
              deriving (Eq)

toFraction :: Int -> Int -> Maybe Fraction
toFraction n d | d == 0 = Nothing
               | otherwise = Just $ simplify (n :-: d)

(!-!) :: Int -> Int -> Maybe Fraction
(!-!) = toFraction

fromPair :: (Int, Int) -> Maybe Fraction
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

maybeShow :: Maybe Fraction -> String
maybeShow (Just f) = show f
maybeShow Nothing = "No fraction here"
