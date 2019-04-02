-- 1. Funkcija koja proverava da li je lista
-- sortirana u strogo rastucem poretku
sortirana :: [Int] -> Bool
sortirana (x:y:xs) = x < y && (sortirana ([y] ++ xs))
sortirana _ = True

pomeriPocetak1 :: [Int] -> Int -> [Int]
pomeriPocetak1 (x:xs) k | x == k = ([x] ++ xs)   
                        | otherwise = pomeriPocetak1 (xs ++ [x]) k

pomeriPocetak :: [Int] -> Int -> [Int]
pomeriPocetak l k | k `elem` l = pomeriPocetak1 l k
                  | otherwise = l

