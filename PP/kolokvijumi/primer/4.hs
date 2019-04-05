sifruj :: [Int] -> Int -> [Int]
sifruj l k
    | mod k 2 == 0 = sifruj1 l k
    | otherwise = sifruj2 l k

menjanje x
    | x>=0 = x+1
    | otherwise = x-1

sifruj1 [] k = []
sifruj1 l k 
    | k > 0 = map (menjanje) (take k l) ++ [sum(take k l)] ++ sifruj1 (drop k l) k
    | otherwise = []

sifruj2 [] k = []
sifruj2 l k 
    | k > 0 = map (menjanje) (take k l) ++ [product(take k l)] ++ sifruj2 (drop k l) k
    | otherwise = []
