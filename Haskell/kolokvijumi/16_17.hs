{- 3. Zadatak-}
-- a)
trougao :: Int -> [(Int, Int, Int)]
trougao n = [(a,b,c) | let rng=[1..n], a <- rng,
                                       b <- rng, 
                                       c <- rng, a + b > c, a + c > b, b + c > a]

{- Try to implement better -}
trougao' :: Int -> [(Int, Int, Int)] 
trougao' n = [(n, n, n)]

-- a)
--
allDifferent (a, b, c) = a/=b && a/=c && b/=c
raznostranicni :: [(Int, Int, Int)] -> Int
raznostranicni l = length (filter allDifferent l)


{- 4. Zadatak-}
--sifruj_cifru :: Int -> Int
--sifruj_cifru c | c < 0 = c - 1 
--               | otherwise = c + 1 
--
--sifruj_k :: [Int] -> Int -> Int
--sifruj_k lista k | k `mod` 2 == 0 = sum lista
--                 | otherwise = product lista
--             
--
--sifruj :: [Int] -> Int -> [Int]
--sifruj [] k = [] 
--sifruj list k = levo ++ [sifruj_k (take k list) k] ++ (sifruj desno k) where
--                levo = map sifruj_cifru (take k list)
--                desno = drop k list

desifruj_cifru :: Int -> Int
desifruj_cifru c | c < 0 = c + 1 
               | otherwise = c - 1 


desifruj :: [Int] -> Int -> [Int]
desifruj [] k = []
desifruj list k = levo ++ (desifruj desno k)
                            where
                                levo = map desifruj_cifru (take k list)  
                                desno = drop (k+1) list
