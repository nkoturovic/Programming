-- Preuzeto iz Lista.hs -------------------------------
data Lista a = Nil | a :-> (Lista a)

showElements :: Show a => Lista a -> String
showElements Nil = ""
showElements (x :-> Nil) = show x
showElements (x :-> xs) = show x ++ ", " ++ showElements xs

fromList :: [a] -> Lista a
fromList [] = Nil
fromList (x:xs) = x :-> fromList xs

toList :: Lista a -> [a]
toList Nil = []
toList (x :-> xs) = [x] ++ toList xs

instance Show a => Show (Lista a) where
  show xs = "{" ++ showElements xs ++ "}"

infixr 5 :->
-------------------------------------------------------
instance Foldable Lista where
    foldr op acc Nil = acc
    foldr op acc (x :-> xs) = foldr op (x `op` acc) xs  

-- Zadavanje tipske klase Reverse
class Reverse a where
    rev :: a -> a

-- Instanca klase za tip List
instance Reverse (Lista a) where
    rev Nil = Nil
    rev xs = foldr (:->) Nil xs

main = print $ rev (1 :-> 2 :-> 3 :-> Nil)
