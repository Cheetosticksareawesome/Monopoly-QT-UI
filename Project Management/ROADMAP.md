# Monopoly — roadmap to a finished game

Updated: 23 September 2026. Based on the current source and saved UI; not a fresh build or playtest.

## Finish line

A Windows desktop game for 2–4 humans sharing one computer: start a game, take legal turns, buy and manage properties, resolve cards and jail, settle debts, reach a winner, save/resume, and start again. Custom names and card flavour are welcome. Choose and document the intended rules before completing advanced mechanics.

**Release 1:** a complete simplified local game through phase 6.
**Finished local edition:** phases 7–10, including the agreed fuller rules.
LAN, bots and experimental events are separate optional expansions, not conditions for finishing local play.

## How to use this

Each checkbox is a task/card with an observable result, not an instruction for each line of code. Do one at a time. If a task introduces several unfamiliar concepts, split it when you reach it. Later phases are a route, not this week's workload.

You write application code. Ask for explanations or review when needed; implementation examples and edits only when requested. Assistant-managed build configuration is separate. Mark work complete after the relevant behaviour is checked, recording whether the evidence is a source review, build, or runtime check.

## Current starting point

Present in source: 40-space board, typed spaces, purchase/rent/mortgage values, owner indices, player-count dialog, two-die values, button connections, movement, buying, rent, taxes, Go rewards, card definitions/effects, jail state, logging, and four Designer pawns.

These features are **partially implemented**, not all verified complete. Important current gaps:

- `UpdatePlayerLabels` creates empty vectors, then populates them only if their size is already greater than one. Neither update loop consequently runs.
- Its pawn code passes `ui.boardLayout[i]` to `setParent`; a grid layout is not an indexed collection of destination widgets. This also appears to be a compile blocker.
- Landing exactly on Go can award money twice: movement awards it, then the Go case awards it again.
- Third doubles can send a player to jail and immediately release them in the same handler.
- `FilterCards` attaches its `else` to the Community Chest check, so valid Chance cards enter the error list.
- Both deck types display in the Chance panel. Movement cards change position without resolving the destination's landing effect.
- Buying checks money/ownership, but does not independently validate the turn stage and purchasable type.
- There is no bankruptcy, winner or new-game flow. Negative money is currently possible.
- Rules and UI are now coupled through movement/card functions. Separate them gradually when useful; do not stop progress for a wholesale rewrite.

## 1. Restore dependable labels and pawns

- [ ] Restore player balance updates. Existing players show their own money; unused labels are hidden.
- [ ] Show one pawn on Go using a valid destination widget. Explain parenting and layout placement before implementing.
- [ ] Make that pawn follow its player's stored position after rolling.
- [ ] Show all active players' pawns, including multiple players sharing one space.
- [ ] Refresh position, balances and pawns after turns, purchases, taxes and cards.
- [ ] Verify one fresh build and two rounds with two players; then check the supported player counts.

**Done when:** visible state agrees with game data and the current source builds.

## 2. Make ordinary turns and landing reliable

- [ ] Award the agreed Go reward once when crossing or landing on Go; check both cases.
- [ ] Reset consecutive doubles correctly and give only the permitted extra rolls.
- [ ] End a turn immediately when a roll sends the player to jail.
- [ ] Offer Buy only for an unowned purchasable space during the allowed turn action.
- [ ] Reject invalid purchases in the purchase operation itself; failed purchases change nothing.
- [ ] Display the new owner and balance immediately after a successful purchase.
- [ ] Resolve affordable rent once per landing; own and unowned properties charge nothing.
- [ ] Let the player finish or decline the purchase decision before the next roll/turn.
- [ ] Show a useful message for rejected purchases, including insufficient funds.

**Done when:** buy, decline, rent, own-property and special-space cases each produce the intended action and button state.

## 3. Complete jail as one coherent rule

- [ ] Write down the jail-entry, release and doubles rules for this edition.
- [ ] Keep visiting separate from being imprisoned.
- [ ] Prevent ordinary movement while imprisoned.
- [ ] Make each chosen release method work, starting with one method.
- [ ] Resolve the last permitted failed attempt and payment without leaving the turn stuck.
- [ ] Check jail from a tile, a card and third doubles, including money and turn state.

**Done when:** every jail route has an exit and no route accidentally releases a newly jailed player.

## 4. Make cards and special spaces dependable

- [ ] Classify each card into the intended deck without falsely logging valid cards.
- [ ] Display each deck's cards in its own panel.
- [ ] Decide whether decks cycle/shuffle or draw with replacement; implement and document that choice.
- [ ] Make money effects agree with the printed card description.
- [ ] Resolve movement-card destinations, including rent, Go and jail, exactly once.
- [ ] Make jail-card payments come from card data rather than an unrelated hard-coded value.
- [ ] Keep card-message timers safe when the window closes or a newer card is displayed.
- [ ] Decide whether Free Parking pays a pot. If so, define and implement contributions.
- [ ] Verify tax amounts and destination effects against the chosen rules.

**Done when:** every enabled card effect works; unimplemented experimental effects cannot silently appear as working cards.

## 5. Make the game understandable to players

- [ ] Highlight the current player and display ownership on properties.
- [ ] Display a short action history for rolls, purchases, rent, taxes and jail.
- [ ] Show affordability clearly; restore normal colours when the state changes.
- [ ] Support readable player names and a clear setup/cancel flow.
- [ ] Keep controls, cards and pawns readable when resizing.
- [ ] Correct board decoration mismatches, including the orange strip at tiles 17/18.

**Done when:** another person can understand whose turn it is, what happened and what they may do next.

## 6. Finish a simplified game — Release 1

- [ ] Define the prototype debt/bankruptcy rule, including remaining money and properties.
- [ ] Handle an unaffordable debt without continuing normal turns with unexplained negative money.
- [ ] Eliminate players and skip them without breaking owner identifiers.
- [ ] Detect the last remaining player and display the winner.
- [ ] Disable game actions after victory.
- [ ] Add New Game with a complete reset of ownership, players, decks, dice and turn state.
- [ ] Play a full two-player game from setup to winner and restart; fix observed blockers.

**Release gate:** a complete local match works. Document simplified rules such as fixed rents or declining without an auction.

## 7. Complete the agreed property system

Consult the selected edition's rules when implementing these; the current data is a prototype.

- [ ] Add colour groups and correct rent for complete groups.
- [ ] Calculate station rent from the owner's station count.
- [ ] Calculate utility rent from the relevant roll and ownership.
- [ ] Run an auction when required after declining a purchase.
- [ ] Build houses with ownership, affordability and even-building restrictions.
- [ ] Add hotels and the bank's building-supply limits.
- [ ] Sell improvements and update rents correctly.
- [ ] Mortgage and unmortgage properties with the chosen restrictions and costs.
- [ ] Allow raising money to settle a debt before bankruptcy.
- [ ] Resolve bankruptcy differently for bank debts and player debts where required.
- [ ] Offer a trade, allow acceptance/rejection, and apply an accepted trade consistently.
- [ ] Complete remaining agreed card effects, including held jail-release cards and repair costs.

**Done when:** the documented rule set is supported without hidden placeholder mechanics.

## 8. Save and resume

- [ ] Decide which game state must survive, including turn phase, decks and pending decisions.
- [ ] Save a versioned game file without overwriting a good save on failure.
- [ ] Validate a load before replacing the active game.
- [ ] Restore the interface from the loaded state.
- [ ] Check resume during an ordinary turn, a purchase decision and jail.
- [ ] Report missing, damaged and incompatible saves clearly.

**Done when:** saving and reopening preserves the next legal action and all money/ownership.

## 9. Reliability and maintainability

- [ ] Add focused checks for Go rewards, turn order, jail, card movement and money transfers.
- [ ] Check rejected purchases/trades leave state unchanged.
- [ ] Gradually isolate rules from widgets where it enables those checks.
- [ ] Make headers declare their dependencies and implementations include their own headers.
- [ ] Keep player identifiers valid across eliminations and new games.
- [ ] Keep logs writable outside the source tree and report useful failures.
- [ ] Stop tracking generated build files; verify a fresh checkout can configure and build.

**Done when:** critical rules can be checked repeatably and the project works from a clean checkout.

## 10. Package the finished local edition

- [ ] Package the executable and required Qt/runtime dependencies.
- [ ] Test it outside the development environment.
- [ ] Add a short README with setup, controls, supported rules and known limitations.
- [ ] Play a complete match with another person and resolve release-blocking issues.
- [ ] Tag a release and keep a small known-issues list.

**Finished when:** someone can install/run, complete, save/resume and restart the documented game without developer assistance.

## Optional expansions — separate decisions

- Bots: legal action selection, basic strategy, visible decisions, full-game checks.
- LAN: authoritative host, validated actions, state synchronization, disconnect/reconnect.
- Experimental cards: define durations, stacking, balancing and save-state effects first.
- Animation, sound and visual polish after the rules remain reliable.

**Immediate next card:** restore the player-label collection so the labels update again.

