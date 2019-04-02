import sys
import os
import re

def create_regex_email():
    """
    Funkcija vraca regex koji prepoznaje e-mail
    Grupa 0 Originalni sadrzaj teksta
    Grupa 1 <username>: Username
    Grupa 2 <provider>: Provajder gmail, hotmail ...
    Grupa 3 <domain>: domain .com .info ...
    """
    username = r'(?P<username>[a-zA-Z][a-zA-Z0-9_]*)'
    provider = r'(?P<provider>[a-zA-Z][a-zA-Z0-9_]*)'
    domain = r'(?P<domain>com|info|rs|net|org)'

    regex = username + r'@' + provider + r'\.' + domain
    return re.compile(regex, flags=re.DOTALL)

regex = create_regex_email()
content = 'necer95@gmail.com example@mail.info\nstress@tess.net'
rezultat = regex.finditer(content)

for r in rezultat:
    print('----------')
    print(r.group(0))
    username = r.group('username')
    provider = r.group('provider')
    domain = r.group('domain')
    print('username:', username)
    print('provider:', provider)
    print('domain:', domain)

print('---ZAMENJENO---')

#zamenjeno = regex.sub(r'\g<provider>@\g<username>.\g<domain>', content)
# zamenjeno = regex.sub(r'\g<2>@\g<1>.\g<3>', content)
# zamenjeno = regex.sub(r'\2@\1.\3', content)
zamenjeno = regex.sub(r'\g<provider>@\g<username>.\g<domain>', content)
print(zamenjeno)
