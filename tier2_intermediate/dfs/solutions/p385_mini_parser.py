import json

from src.wasm_libs.py.io import read_line, write_string


class NestedInteger:
    def __init__(self, value=None):
        if value is None:
            self._list: list[NestedInteger] = []
        else:
            self._integer: int = value
            self._list = None

    def isInteger(self) -> bool:
        return self._list is None

    def add(self, elem: "NestedInteger"):
        self._list.append(elem)

    def _to_python(self):
        if self.isInteger():
            return self.getInteger()
        return [item._to_python() for item in self.getList()]

    def getInteger(self) -> int | None:
        return self._integer if self._list is None else None

    def getList(self) -> list["NestedInteger"] | None:
        return self._list if self._list is not None else None


def deserialize(s: str) -> NestedInteger:
    if not s.startswith("["):
        return NestedInteger(int(s))
    stack: list[NestedInteger] = []
    current = NestedInteger()
    i = 0
    while i < len(s):
        if s[i] == "[":
            new_ni = NestedInteger()
            if stack:
                stack[-1].add(new_ni)
            stack.append(new_ni)
            current = new_ni
            i += 1
        elif s[i] == "]":
            finished = stack.pop()
            current = finished
            i += 1
        elif s[i] == ",":
            i += 1
        else:
            j = i
            while j < len(s) and (s[j].isdigit() or s[j] == "-"):
                j += 1
            num = NestedInteger(int(s[i:j]))
            if stack:
                stack[-1].add(num)
            else:
                current = num
            i = j
    return current


def main():
    s = read_line()
    result = deserialize(s)
    if result.isInteger():
        write_string(str(result.getInteger()))
    else:
        write_string(json.dumps(result._to_python()))


if __name__ == "__main__":
    main()
