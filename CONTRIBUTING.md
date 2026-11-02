# Contributing

This follows the quality-management process in our Initial Project Plan:
every change is reviewed before it reaches `main`.

## Workflow

1. Update `main`: `git switch main && git pull`
2. Create a branch for your change:
   `git switch -c firmware/lcd-driver`
3. Commit small, working steps (see commit messages below).
4. Push the branch: `git push -u origin firmware/lcd-driver`
5. Open a pull request into `main` on GitHub and fill in the template.
6. Get at least **one approving review**, then merge.

Never push directly to `main`.

## Branch names

`<area>/<short-description>`, where area is one of `firmware`, `hardware`,
`enclosure` or `docs`. For example: `firmware/ad9833-driver`,
`hardware/front-end-schematic`, `enclosure/lid-v2`.

## Commit messages

- First line: a short summary in the imperative, ≤ 72 characters.
  e.g. `Add AD9833 frequency-setting function`, not `stuff` or `fixed it`.
- Add a blank line and more detail if the change needs explaining.

Good commit messages are evidence for our individual reports, so make them
say what you actually did.

## Reviews

| Area       | Reviewer                                        |
| ---------- | ----------------------------------------------- |
| Firmware   | Bradley (Embedded Programming Leader); Bradley's own code is reviewed by another member |
| Hardware   | Juncheng (Hardware Leader)                      |
| Enclosure  | Raisa (Mechanical Design Leader)                |

Reviewers should check that the change builds, does what the PR says, and is
readable and commented. Leave comments on GitHub; the author resolves them.

## Line endings

`.gitattributes` normalises line endings, so Windows and Linux users can work
on the same files. Don't change your `core.autocrlf` setting to work around
it.
