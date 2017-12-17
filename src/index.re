open Reprocessing;

/* UI Constants */
let windowWidth = 600.;
let windowHeight = 600.;
let spaceShipWidth = 50.;
let spaceShipHeight = 5.;

/* Type declarations */
type coordinateT = (float, float);

type stateT = {
  started: bool,
  ship: coordinateT,
  missiles: list(coordinateT)
};

/* Scene helpers */
let coordinateToDraw = (~coordinateT: coordinateT) => {
  let (x, y) = coordinateT;

  (
    int_of_float(x),
    int_of_float(y)
  )
};

let moveBy = (~origin: coordinateT, ~by: (float, float)) => {
  let (originX, originY) = origin;
  let (byX, byY) = by;

  (
    originX +. byX,
    originY +. byY
  )
};

/* state helpers */
let initialState = () => {
  {
    started: false,
    ship: ((windowWidth -. spaceShipWidth) /. 2., windowHeight -. 20.),
    missiles: []
  }
};

let setup = (env) => {
  Env.size(~width=int_of_float(windowWidth), ~height=int_of_float(windowHeight), env);
  initialState()
};

let draw = ({started, ship} as state, env) => {
  Draw.background(Constants.black, env);
  Draw.fill(Constants.green, env);
  Draw.rect(~pos=coordinateToDraw(ship),
            ~width=int_of_float(spaceShipWidth),
            ~height=int_of_float(spaceShipHeight),
            env);
  state
};

let keyPressed = (state, env) => {
  Events.(
    switch (Env.keyCode(env)) {
    | Space => { ...state, started: true }
    | (Left | A) => { ...state, ship: moveBy(state.ship, (-1., 0.)) }
    | (Right | D) => { ...state, ship: moveBy(state.ship, (1., 0.)) }
    | _ => state
    }
  )

};

let keyReleased = (state, env) => {
  state
};


run(~setup, ~draw, ~keyPressed, ~keyReleased, ());


