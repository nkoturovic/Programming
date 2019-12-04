module MyList
    ( MyList (II)
    , MyList ((:->))
    , (+:+)
    ) where

infixr 7 :->
data MyList a = II
              | a :-> (MyList a)
              deriving ( Eq )

infixr 6 +:+
(+:+) II rs = rs
(+:+) (l:->II) rs = l :-> rs
(+:+) (l:->ls) rs = l :-> (ls +:+ rs)
 
showElements II = ""
showElements (a :-> II) = show a 
showElements (a :-> b :-> II) = show a ++ "," ++ show b
showElements (a :-> b) = show a ++ "," ++ showElements b

instance (Show a) => Show (MyList a) where
    show l = "I" ++ showElements l ++ "I"

instance Functor MyList where
    fmap func II = II
    fmap func (x :-> xs) = func x :-> fmap func xs

instance Foldable MyList where
    foldl f acc II = acc
    foldl f acc (l :-> ls) = foldl f (acc `f` l) ls 
    foldr f init II = init
    foldr f init (r :-> rs) = f r (foldr f init rs)
