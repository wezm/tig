#define SIZEOF_REV	41	/* Holds a SHA-1 and an ending NUL */

/* Revision graph */

#define REVGRAPH_INIT	'I'
#define REVGRAPH_MERGE	'M'
#define REVGRAPH_BRANCH	'+'
#define REVGRAPH_COMMIT	'*'
#define REVGRAPH_LINE	'|'

/* Size of rev graph with no  "padding" columns */
#define SIZEOF_REVITEMS	(SIZEOF_REVGRAPH - (SIZEOF_REVGRAPH / 2))

	char id[SIZEOF_REV];	/* Commit SHA1 ID */
LINE(ACKED,	   "    Acked-by",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \
do_scroll_view(struct view *view, int lines)
	bool redraw_current_line = FALSE;
	/* Move current line into the view. */
	if (view->lineno < view->offset) {
		view->lineno = view->offset;
		redraw_current_line = TRUE;
	} else if (view->lineno >= view->offset + view->height) {
		view->lineno = view->offset + view->height - 1;
		redraw_current_line = TRUE;
	}

	assert(view->offset <= view->lineno && view->lineno < view->lines);

		if (redraw_current_line)
			draw_view_line(view, view->lineno - view->offset);
	assert(view_is_displayed(view));

	do_scroll_view(view, lines);
move_view(struct view *view, enum request request)
	int scroll_steps = 0;
		scroll_steps = steps;
			scroll_steps = -view->offset;
				scroll_steps = view->lines - view->offset - 1;
				if (scroll_steps >= view->height)
					scroll_steps -= view->height - 1;
	}
	if (!view_is_displayed(view)) {
		view->offset += steps;
		view->ops->select(view, &view->line[view->lineno]);
	/* Repaint the old "current" line if we be scrolling */
	if (ABS(steps) < view->height)
		draw_view_line(view, view->lineno - steps - view->offset);
	if (scroll_steps) {
		do_scroll_view(view, scroll_steps);
	}

	/* Draw the current line */
	draw_view_line(view, view->lineno - view->offset);
static void search_view(struct view *view, enum request request);
			search_view(view, request);
search_view(struct view *view, enum request request)
	regex_err = regcomp(view->regex, opt_search, REG_EXTENDED);
	string_copy(view->grep, opt_search);
		do_scroll_view(prev, lines);
		move_view(view, request);
			move_view(view, request);
			if (view_is_displayed(view))
			move_view(view, request);
		search_view(view, request);
/* Parse output from git-ls-tree(1):
	enum open_flags flags = display[0] == view ? OPEN_SPLIT : OPEN_DEFAULT;
			char *data = line->data;
	char *text = line->data;

	text += STRING_SIZE("100644 blob ");
	if (line->type == LINE_TREE_FILE) {
		string_ncopy(ref_blob, text, 40);
		/* Also update the blob view's ref, since all there must always
		 * be in sync. */
		string_copy(VIEW(REQ_VIEW_BLOB)->ref, ref_blob);

	} else if (line->type != LINE_TREE_DIR) {
		return;

	string_ncopy(view->ref, text, 40);
	char id[SIZEOF_REV];		/* SHA1 ID. */

struct rev_stack {
	struct rev_stack *prev, *next, *parents;
	char rev[SIZEOF_REVITEMS][SIZEOF_REV];
	size_t size;
	struct commit *commit;
	size_t pos;
};

/* Parents of the commit being visualized. */
static struct rev_stack graph_parents[3];

/* The current stack of revisions on the graph. */
static struct rev_stack graph_stacks[3] = {
	{ &graph_stacks[2], &graph_stacks[1], &graph_parents[0] },
	{ &graph_stacks[0], &graph_stacks[2], &graph_parents[1] },
	{ &graph_stacks[1], &graph_stacks[0], &graph_parents[2] },
};

static inline bool
graph_parent_is_merge(struct rev_stack *graph)
{
	return graph->parents->size > 1;
}

static void
reset_rev_graph(struct rev_stack *graph)
{
	graph->size = graph->pos = 0;
	graph->commit = NULL;
	memset(graph->parents, 0, sizeof(*graph->parents));
}

static inline void
append_to_rev_graph(struct rev_stack *stack, chtype symbol)
{
	if (stack->commit->graph_size < ARRAY_SIZE(stack->commit->graph) - 1)
		stack->commit->graph[stack->commit->graph_size++] = symbol;
}

static void
push_rev_stack(struct rev_stack *stack, char *parent)
{
	/* Combine duplicate parents lines. */
	if (stack->size > 0 &&
	    !strncmp(stack->rev[stack->size - 1], parent, SIZEOF_REV))
		return;

	if (stack->size < SIZEOF_REVITEMS) {
		string_ncopy(stack->rev[stack->size++], parent, SIZEOF_REV);
	}
}

static void
draw_rev_graph(struct rev_stack *graph)
{
	chtype symbol, separator, line;
	size_t i;

	/* Place the symbol for this commit. */
	if (graph->parents->size == 0)
		symbol = REVGRAPH_INIT;
	else if (graph->parents->size > 1)
		symbol = REVGRAPH_MERGE;
	else if (graph->pos >= graph->size)
		symbol = REVGRAPH_BRANCH;
	else
		symbol = REVGRAPH_COMMIT;

	separator = ' ';
	line = REVGRAPH_LINE;

	for (i = 0; i < graph->pos; i++) {
		append_to_rev_graph(graph, line);
		if (graph_parent_is_merge(graph->prev) &&
		    graph->prev->pos == i) {
			separator = '`';
			line = '.';
		}
		append_to_rev_graph(graph, separator);
	}

	append_to_rev_graph(graph, symbol);

	if (graph->prev->size > graph->size) {
		separator = '\'';
		line = ' ';
	} else {
		separator = ' ';
		line = REVGRAPH_LINE;
	}
	i++;

	for (; i < graph->size; i++) {
		append_to_rev_graph(graph, separator);
		append_to_rev_graph(graph, line);
		if (graph_parent_is_merge(graph->prev)) {
			if (i < graph->prev->pos + graph->parents->size) {
				separator = '`';
				line = '.';
			}
		}
		if (graph->prev->size > graph->size) {
			separator = '/';
			line = ' ';
		}
	}

	if (graph->prev->size > graph->size) {
		append_to_rev_graph(graph, separator);
		if (line != ' ')
			append_to_rev_graph(graph, line);
	}
}

void
update_rev_graph(struct rev_stack *graph)
{
	size_t i;

	/* First traverse all lines of revisions up to the active one. */
	for (graph->pos = 0; graph->pos < graph->size; graph->pos++) {
		if (!strcmp(graph->rev[graph->pos], graph->commit->id))
			break;

		push_rev_stack(graph->next, graph->rev[graph->pos]);
	}

	for (i = 0; i < graph->parents->size; i++)
		push_rev_stack(graph->next, graph->parents->rev[i]);

	/* FIXME: Moving branches left and right when collapsing a branch. */
	for (i = graph->pos + 1; i < graph->size; i++)
		push_rev_stack(graph->next, graph->rev[i]);

	draw_rev_graph(graph);

	if (graph_parent_is_merge(graph->prev) &&
	    graph->prev->pos < graph->prev->size - 1 &&
	    graph->size == graph->prev->size + graph->prev->parents->size - 1) {
		i = graph->prev->pos + graph->prev->parents->size - 1;
		graph->prev->commit->graph_size = i * 2;
		while (i < graph->size - 1) {
			append_to_rev_graph(graph->prev, ' ');
			append_to_rev_graph(graph->prev, '\\');
			i++;
		}
	}

	reset_rev_graph(graph->prev);
}

	static struct rev_stack *graph = graph_stacks;
		graph->commit = commit;
		break;

	case LINE_PARENT:
		if (commit) {
			line += STRING_SIZE("parent ");
			push_rev_stack(graph->parents, line);
		}
		update_rev_graph(graph);
		graph = graph->next;
