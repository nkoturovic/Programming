--Zadatak 3.6
lista :: Int -> Int -> [Int]
lista a b = [a..b]

--Zadatak 3.7
parMax :: (Double, Double) -> Double
parMax p | fst p > snd p = fst p
	 | otherwise = snd p
--Another solution
parMax1 :: Ord p => (p, p) -> p
parMax1 p | fst p > snd p = fst p
	 | otherwise = snd p


--Zadatak 3.14
-- harm o | o < o = o
-- 	| otherwise = o

-- El. Harmonijskog reda
harm_red :: (Eq n, Fractional n) => n -> n
harm_red 1 = 1.0
harm_red n = harm_red(n-1) + 1/n

-- El. Harmonijskog niza
harm_niz n = 1/n

-- Red II nacin
harm_red1 1 = harm_niz 1
harm_red1 n = harm_niz n + harm_red1(n-1)

-- List comperhensions
[(x, y) | x <- [0..5], y <- [0..5], x + y == 5]

prirodni n = [
