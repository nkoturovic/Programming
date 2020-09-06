-- Ukoliko se zarobis u svetu IO monada, ne mozes izaci iz njega,
-- tj. ukoliko udjemo u unpure svet, ne mozemo izaci

data Kutija a = Zapakuj a

instance Functor Kutija where
    -- fmap :: (a -> b) -> Kutija a -> Kutija b
    fmap f (Zapakuj a) = Zapakuj $ f a

instance Applicative Kutija where
    -- (<*>) :: Kutija (a -> b) -> Kutija a -> Kutija b
    (Zapakuj f) <*> (Zapakuj a) = Zapakuj $ f a
    -- pure :: a -> Kutija a
    pure a = Zapakuj a

instance Monad Kutija where
    -- return :: a -> Kutija a
    return = Zapakuj
    -- (>>=) :: Kutija a -> (a -> Kutija b) -> Kutija b
    (Zapakuj a) >>= f = f a

-- Primer koriscenja monada Kutija
getStringPure :: Kutija String
getStringPure = Zapakuj "The quick brown fox jumps over the lazy dog"

putStrLnPure :: String -> Kutija ()
putStrLnPure str = Zapakuj () 

pureMain = getStringPure >>= putStrLnPure

pureMainDo = do
    str <- getStringPure
    putStrLnPure str 

main = getLine >>= putStrLn

mainDo = do
    line <- getLine
    putStrLn line
