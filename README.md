# Todo

## MVP

- [x] Complete kaitai grammar
- [ ] Check for and extract extension data
- [ ] Access/stream data array ?
  - [ ] -> Probably just give the user utils for byte swapping chunks and to calculate offsets


## Nice to have

- [ ] Add function: Validate header standard compliance
- [ ] Normalize header (to affine method)
  - [ ] Convert between orientation methods
  - [ ] Maybe also include pixdim ? (look how nibabel does it)
- [ ] Dynamic dispatch for different header versions (?)


## Platform support

- [ ] Generate numpy headers
- [ ] Generate R headers (?)

- [ ] Compile to webassembly (?) and write JS wrapper
  - [ ] Read header in shared memory -> predict offsets -> read/interpret data