#!/usr/bin/env python3
"""Recommends 4 Div.2 like problems from Codeforces."""

import json
import random
import sys
import urllib.request
import re

DIV2_PATTERNS = [
    re.compile(r"div\.\s*2", re.I),
    re.compile(r"educational", re.I),
    re.compile(r"div\.\s*1\s*\+\s*2", re.I),
    re.compile(r"global\s*round", re.I),
    re.compile(r"hello\s*\d{4}", re.I),
    re.compile(r"good\s*bye\s*\d{4}", re.I),
]

DIV1_ONLY = re.compile(r"div\.\s*1(?!\s*\+)", re.I)
DIV2_CHECK = re.compile(r"div\.\s*2", re.I)

DEFAULT_RANGES = [
    {"letter": "B", "L": 1200, "R": 2100},
    {"letter": "C", "L": 1300, "R": 2100},
    {"letter": "B", "L": 1200, "R": 2100},
    {"letter": "C", "L": 1300, "R": 2100},
]

RATING_COLORS = {
    1200: "\033[90m",    # gray   - newbie
    1400: "\033[32m",    # green  - pupil
    1600: "\033[36m",    # cyan   - specialist
    1900: "\033[34m",    # blue   - expert
    2100: "\033[35m",    # purple - candidate master
    2400: "\033[33m",    # orange - master
    9999: "\033[31m",    # red    - grandmaster
}
RESET = "\033[0m"


def colored_rating(rating):
    if not rating:
        return "\033[90m?\033[0m"
    for threshold, color in RATING_COLORS.items():
        if rating < threshold:
            return f"{color}{rating}{RESET}"
    return f"\033[31m{rating}{RESET}"


def api_get(url):
    req = urllib.request.Request(url, headers={"User-Agent": "cfgrind-cli/1.0"})
    with urllib.request.urlopen(req, timeout=30) as resp:
        data = json.loads(resp.read().decode())
    if data.get("status") != "OK":
        raise Exception(data.get("comment", "API error"))
    return data["result"]


def is_div2_like(name):
    if DIV1_ONLY.search(name) and not DIV2_CHECK.search(name):
        return False
    return any(p.search(name) for p in DIV2_PATTERNS)


def fetch_solved(handle):
    print(f"  Buscando submissões de {handle}...")
    subs = api_get(f"https://codeforces.com/api/user.status?handle={handle}&from=1&count=100000")
    solved = set()
    for s in subs:
        if s.get("verdict") == "OK":
            p = s["problem"]
            solved.add(f"{p['contestId']}-{p['index']}")
    return solved


def fetch_problems_and_contests():
    print("  Carregando problemas e contests...")
    problems = api_get("https://codeforces.com/api/problemset.problems")["problems"]
    contests_list = api_get("https://codeforces.com/api/contest.list?gym=false")
    contests = {c["id"]: c["name"] for c in contests_list}
    return problems, contests


def recommend(letter, L, R, problems, contests, solved):
    candidates = [
        p for p in problems
        if p["index"] == letter
        and p.get("rating")
        and p["contestId"] >= 1300
        and contests.get(p["contestId"])
        and is_div2_like(contests[p["contestId"]])
        and f"{p['contestId']}-{p['index']}" not in solved
    ]
    for rating in range(L, R + 1, 100):
        at_rating = [p for p in candidates if p.get("rating") == rating]
        if at_rating:
            return random.choice(at_rating)
    return None


def main():
    handle = sys.argv[1] if len(sys.argv) > 1 else input("Handle do Codeforces: ").strip()
    if not handle:
        print("Handle vazio. Saindo.")
        sys.exit(1)

    print()
    solved = fetch_solved(handle)
    problems, contests = fetch_problems_and_contests()
    print()

    print(f"{'─' * 60}")
    print(f"  Problemas para {handle}")
    print(f"{'─' * 60}")

    for i, r in enumerate(DEFAULT_RANGES, 1):
        p = recommend(r["letter"], r["L"], r["R"], problems, contests, solved)
        if p:
            rating_str = colored_rating(p.get("rating"))
            url = f"https://codeforces.com/contest/{p['contestId']}/problem/{p['index']}"
            print(f"  {i}. [{p['index']}] {p['name']}  ({rating_str})")
            print(f"     {url}")
        else:
            print(f"  {i}. [{r['letter']}] Nenhum problema encontrado ({r['L']}–{r['R']})")
        print()

    print(f"{'─' * 60}")
    print("  Bom solving!")
    print(f"{'─' * 60}")


if __name__ == "__main__":
    main()
