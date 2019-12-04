import qualified Data.Char as Ch

-- Funkcija koja transformise velika
-- slova u mala a mala slova u velika
changeCase :: Char -> Char
changeCase c
    | Ch.isUpper c = Ch.toLower c
    | Ch.isLower c = Ch.toUpper c
    | otherwise = c

-- Funkcija koja pravi sifrovanu poruku
encode :: String -> String
encode = reverse . map (changeCase . succ)

-- Funkcija koja desifruje sifrovanu poruku
decode :: String -> String
decode = reverse . map (changeCase . pred)

main :: IO()
main = do
    input <- getLine
    let e = encode input
    let d = decode e
    putStrLn ("Secret message is: " ++ e)
    putStrLn ("Decoded message is: " ++ d)
