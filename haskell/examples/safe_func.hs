safeDiv :: (Floating a, Ord a) => a -> a -> Maybe a
_ `safeDiv` 0.0 = Nothing
b `safeDiv` i = Just $ b/i

(%) :: (Floating a, Ord a) => a -> a -> Maybe a
(%) = safeDiv

safeSqrt :: (Floating a, Ord a) => a -> Maybe a
safeSqrt x | x < 0 = Nothing
           | otherwise = Just $ sqrt x

safeFunc :: (Floating a, Ord a) => a -> a -> Maybe a
safeFunc x y = (x `safeDiv` y) >>= safeSqrt

safeFuncDo :: (Floating a, Ord a) => a -> a -> Maybe a
safeFuncDo x y = do
    divResult <- x `safeDiv` y
    safeSqrt divResult

main :: IO ()
main = do
    let result = safeFuncDo 1.0 2.0
    print result
