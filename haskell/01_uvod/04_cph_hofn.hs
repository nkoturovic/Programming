{-- List comperhensions --}
take 6 [2^n | n <- [1..], n `mod` 2 == 0]
headsTails = [ if x < 5 then "heads" else "tails" | x <- [1..10], odd x]   
[f x | x <- xs, g x] -- f(x) if g(x) is true for x from xs
[(\x -> x + 1) x | x <- [1,2], (\x -> x==1) x]

{-- Higher order functions --}
xs = [1,2,3,4]
map (^2) xs -- Mapping result: [1,4,9,16]
map (\e -> e*e) [1,2] -- Mapping result: [1,2,1,4]
odd's = filter (\n -> n `mod` 2 == 1) xs -- filter: [1,3]
sum_of_xs = foldl (\x y -> x + y) 0 xs -- fold(l/r) (reduce/acc): 10

hasThree = any (\e -> e == 3) xs -- any el. sat. lambda: True
or [False, False, True, False] -- Check if any true: True
and [False, False, True, False] -- Check if all true: False
all (\e -> e^2 > 10) [4,5,6] -- Lambda True 4all: True
takeWhile (>=3) [5,4,3,2,1] -- Takes while >=3: [5,4,3]

{-- Precedence'$' and composition '.' operators --}
-- Precendence:
(4 *) $ 3 + 2 -- Calculates 3+2, then * 4: result = 20
(4 *) 3 + 2   -- Calculates 4*3, then + 2: result = 14 

-- Composition/application:
h = (\e -> -e) . (\e -> e^2) -- f.g = f(g(x))
{--     f      .      g      =        f(g(x)) --}
h' x = (\e -> -e) $ (\e -> e^2) $ x --f(g(x))

-- In a chain of $-s, all but the final one can be replaced by .
f $ g $ h $ x <=> f . g . h $x <=> f . g . h  -- f(g(h(x))

{-- calculates 1+1, makes composition of --} 
{-- putStrLn and show and call it with 2 --}
putStrLn . show $ 1 + 1
