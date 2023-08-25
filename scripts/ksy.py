from dataclasses import dataclass
from typing import List, Optional
import yaml

@dataclass
class KsyEnumValue:
    name: str
    value: int
    doc: Optional[str] = None


@dataclass
class KsyEnum:
    name: str
    values: List[KsyEnumValue]
    
    def __init__(self, name: str, ksy: dict):
        self.name = name
        ksy = ksy['enums'][name]
        self.values = []
        for var_value, var_name in ksy.items():
            if isinstance(var_name, dict):
                self.values.append(KsyEnumValue(
                    name=var_name['id'],
                    value=var_value,
                    doc=var_name['doc'] if 'doc' in var_name else None
                ))
            else:
                self.values.append(KsyEnumValue(
                    name=var_name,
                    value=var_value,
                    doc=None
                ))



class KsyGrammar:
    def __init__(self, filename) -> None:
        with open(filename) as f:
            ksy = yaml.load(f, Loader=yaml.FullLoader)

        self.ksy = ksy
    
    def iter_enums(self):
        for enum_name in self.ksy['enums'].keys():
            yield KsyEnum(enum_name, self.ksy)

    def n1(self) -> dict:
        return self.ksy['types']['n1_file']
    
    def n2(self) -> dict:
        return self.ksy['types']['n2_file']