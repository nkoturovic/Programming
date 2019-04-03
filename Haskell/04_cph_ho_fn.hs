(\a b -> a + b) -- lambda
{-- List comperhensions --}
[sqrt x | x <- xs, x >= 0] -- or x >= 0
take 6 [2^n | n <- [1..], n `mod` 2 == 0]
boomBangs = [ if x < 5 then "BOOM!" else "BANG!" | x <- [1..10], odd x]   
[f x | x <- xs, g x] -- f(x) if g(x) is true for x from xs
[(\x -> x + 1) x | x <- [1,2], (\x -> x==1) x]

-- Higher order functions
xs = [1,2,3,4]
map (^2) xs -- map -> [1,4,9,16]
odd's = filter (\n -> n `mod` 2 == 1) xs -- filter: [1,3]
sum_of_xs = foldl (\x y -> x + y) 0 xs -- fold(l/r) (reduce/acc): 10
hasThree = any (\e -> e == 3) xs -- any el. sat. lambda: True
