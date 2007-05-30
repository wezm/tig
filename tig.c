#define VERSION	"tig-0.6.git"
	"git ls-remote $(git rev-parse --git-dir) 2>/dev/null"
	unsigned int remote:1;	/* Is it a remote ref? */
#define string_copy_rev(dst, src) \
	string_ncopy_do(dst, SIZEOF_REV, src, SIZEOF_REV - 1)

	if (bufsize < SIZEOF_STR)
		buf[bufsize] = 0;

static bool opt_rev_graph		= FALSE;
		if (!strcmp(opt, "log") ||
		    !strcmp(opt, "diff") ||
		    !strcmp(opt, "show")) {
			opt_request = opt[0] == 'l'
				    ? REQ_VIEW_LOG : REQ_VIEW_DIFF;
			break;
		}

		if (opt[0] && opt[0] != '-')
			break;

			string_copy(opt_cmd, "git log --pretty=raw");
LINE(MAIN_REMOTE,  "",			COLOR_YELLOW,	COLOR_DEFAULT,	A_BOLD), \
	char *sep = "";
/* Reading from the prompt? */
static bool input_mode = FALSE;

	/* Open and reads in all view content. */
	bool (*open)(struct view *view);
	/* Draw one line; @lineno must be < view->height. */
	bool (*draw)(struct view *view, struct line *line, unsigned int lineno, bool selected);
static struct view_ops help_ops;
	VIEW_(HELP,  "help",  &help_ops,  ""),
	VIEW_(PAGER, "pager", &pager_ops, ""),
	bool draw_ok;
	scrollok(view->win, FALSE);
	draw_ok = view->ops->draw(view, line, lineno, selected);
	scrollok(view->win, TRUE);

	return draw_ok;
	if (input_mode)
		wnoutrefresh(view->win);
	else
		wrefresh(view->win);
	char buf[SIZEOF_STR];
	char state[SIZEOF_STR];
	size_t bufpos = 0, statelen = 0;
	assert(view_is_displayed(view));
		string_format_from(state, &statelen, "- %s %d of %d (%d%%)",
				   view->ops->type,
				   view->lineno + 1,
				   view->lines,
				   lines);

		if (view->pipe) {
			time_t secs = time(NULL) - view->start_time;

			/* Three git seconds are a long time ... */
			if (secs > 2)
				string_format_from(state, &statelen, " %lds", secs);
		}
	string_format_from(buf, &bufpos, "[%s]", view->name);
	if (*view->ref && bufpos < view->width) {
		size_t refsize = strlen(view->ref);
		size_t minsize = bufpos + 1 + /* abbrev= */ 7 + 1 + statelen;

		if (minsize < view->width)
			refsize = view->width - minsize + 7;
		string_format_from(buf, &bufpos, " %.*s", refsize, view->ref);
	}
	if (statelen && bufpos < view->width) {
		string_format_from(buf, &bufpos, " %s", state);
	if (view == display[current_view])
		wbkgdset(view->title, get_line_attr(LINE_TITLE_FOCUS));
	else
		wbkgdset(view->title, get_line_attr(LINE_TITLE_BLUR));

	mvwaddnstr(view->title, 0, 0, buf, bufpos);
	wclrtoeol(view->title);

	if (input_mode)
		wnoutrefresh(view->title);
	else
		wrefresh(view->title);
update_display_cursor(struct view *view)
		view->offset += scroll_steps;
		assert(0 <= view->offset && view->offset < view->lines);
		/* When running random commands, initially show the
		 * command in the title. However, it maybe later be
		 * overwritten if a commit line is selected. */
		string_copy(view->ref, view->cmd);
		char path[SIZEOF_STR];
			opt_path[0] = path[0] = 0;
		else if (sq_quote(path, 0, opt_path) >= sizeof(path))
			return FALSE;
		if (!string_format(view->cmd, format, id, path))

		/* Put the current ref_* value to the view title ref
		 * member. This is needed by the blob view. Most other
		 * views sets it automatically after loading because the
		 * first line is a commit line. */
		string_copy(view->ref, id);
	string_copy_rev(view->vid, id);
		/* Since revision graph visualization requires knowledge
		 * about the parent commit, it causes a further one-off
		 * needed to be redrawn for incremental updates. */
		if (redraw_from > 0 && opt_rev_graph)
			redraw_from--;

	view->ops->read(view, NULL);
static struct line *
add_line_data(struct view *view, void *data, enum line_type type)
	struct line *line = &view->line[view->lines++];
	memset(line, 0, sizeof(*line));
	line->type = type;
	line->data = data;
	return line;
}
static struct line *
add_line_text(struct view *view, char *data, enum line_type type)
{
	if (data)
		data = strdup(data);
	return data ? add_line_data(view, data, type) : NULL;
}
/*
 * View opening
 */
	if (view->ops->open) {
		if (!view->ops->open(view)) {
			report("Failed to load %s view", view->name);
			return;
		}
			report("No file chosen, press %s to open tree view",
			       get_key(REQ_VIEW_TREE));
		open_view(view, request, OPEN_DEFAULT);
		break;

	case REQ_VIEW_PAGER:
		if (!VIEW(REQ_VIEW_PAGER)->lines) {
			report("No pager content, press %s to run command from prompt",
			       get_key(REQ_PROMPT));
			break;
		}
		open_view(view, request, OPEN_DEFAULT);
		break;

	if (!string_format(refbuf, "git describe %s 2>/dev/null", commit_id))
		char *fmt = ref->tag    ? "%s[%s]" :
		            ref->remote ? "%s<%s>" : "%s%s";
	add_line_text(view, buf, LINE_PP_REFS);
	struct line *line;
	if (!data)
		return TRUE;
	line = add_line_text(view, data, get_line_type(data));
	if (!line)
		return FALSE;
		char *text = line->data + STRING_SIZE("commit ");
		if (view != VIEW(REQ_VIEW_PAGER))
			string_copy_rev(view->ref, text);
		string_copy_rev(ref_commit, text);
	NULL,
	pager_draw,
	pager_enter,
	pager_grep,
	pager_select,
};


/*
 * Help backend
 */

static bool
help_open(struct view *view)
{
	char buf[BUFSIZ];
	int lines = ARRAY_SIZE(req_info) + 2;
	int i;

	if (view->lines > 0)
		return TRUE;

	for (i = 0; i < ARRAY_SIZE(req_info); i++)
		if (!req_info[i].request)
			lines++;

	view->line = calloc(lines, sizeof(*view->line));
	if (!view->line)
		return FALSE;

	add_line_text(view, "Quick reference for tig keybindings:", LINE_DEFAULT);

	for (i = 0; i < ARRAY_SIZE(req_info); i++) {
		char *key;

		if (!req_info[i].request) {
			add_line_text(view, "", LINE_DEFAULT);
			add_line_text(view, req_info[i].help, LINE_DEFAULT);
			continue;
		}

		key = get_key(req_info[i].request);
		if (!string_format(buf, "    %-25s %s", key, req_info[i].help))
			continue;

		add_line_text(view, buf, LINE_DEFAULT);
	}

	return TRUE;
}

static struct view_ops help_ops = {
	"line",
	help_open,
	NULL,
	pager_draw,
	size_t textlen = text ? strlen(text) : 0;
		if (!string_format(buf, "Directory path /%s", opt_path) ||
		    !realloc_lines(view, view->line_size + 1) ||
		    !add_line_text(view, buf, LINE_DEFAULT))
		if (*opt_path) {
			if (!string_format(buf, TREE_UP_FORMAT, view->ref) ||
			    !realloc_lines(view, view->line_size + 1) ||
			    !add_line_text(view, buf, LINE_TREE_DIR))
				return FALSE;
		}
	if (!add_line_text(view, text, type))
	enum open_flags flags;
		flags = OPEN_RELOAD;
		flags = display[0] == view ? OPEN_SPLIT : OPEN_DEFAULT;
	char *text = line->data + STRING_SIZE("100644 blob ");
		string_copy_rev(ref_blob, text);
	string_copy_rev(view->ref, text);
	NULL,
	pager_draw,
	return add_line_text(view, line, LINE_DEFAULT);
	NULL,
	pager_draw,
 * Revision graph
	char title[128];		/* First line of the commit message. */
/* Size of rev graph with no  "padding" columns */
#define SIZEOF_REVITEMS	(SIZEOF_REVGRAPH - (SIZEOF_REVGRAPH / 2))

struct rev_graph {
	struct rev_graph *prev, *next, *parents;
	char rev[SIZEOF_REVITEMS][SIZEOF_REV];
	size_t size;
	struct commit *commit;
	size_t pos;
};

/* Parents of the commit being visualized. */
static struct rev_graph graph_parents[4];

/* The current stack of revisions on the graph. */
static struct rev_graph graph_stacks[4] = {
	{ &graph_stacks[3], &graph_stacks[1], &graph_parents[0] },
	{ &graph_stacks[0], &graph_stacks[2], &graph_parents[1] },
	{ &graph_stacks[1], &graph_stacks[3], &graph_parents[2] },
	{ &graph_stacks[2], &graph_stacks[0], &graph_parents[3] },
};

static inline bool
graph_parent_is_merge(struct rev_graph *graph)
{
	return graph->parents->size > 1;
}

static inline void
append_to_rev_graph(struct rev_graph *graph, chtype symbol)
{
	struct commit *commit = graph->commit;

	if (commit->graph_size < ARRAY_SIZE(commit->graph) - 1)
		commit->graph[commit->graph_size++] = symbol;
}

static void
done_rev_graph(struct rev_graph *graph)
{
	if (graph_parent_is_merge(graph) &&
	    graph->pos < graph->size - 1 &&
	    graph->next->size == graph->size + graph->parents->size - 1) {
		size_t i = graph->pos + graph->parents->size - 1;

		graph->commit->graph_size = i * 2;
		while (i < graph->next->size - 1) {
			append_to_rev_graph(graph, ' ');
			append_to_rev_graph(graph, '\\');
			i++;
		}
	}

	graph->size = graph->pos = 0;
	graph->commit = NULL;
	memset(graph->parents, 0, sizeof(*graph->parents));
}

static void
push_rev_graph(struct rev_graph *graph, char *parent)
{
	int i;

	/* "Collapse" duplicate parents lines.
	 *
	 * FIXME: This needs to also update update the drawn graph but
	 * for now it just serves as a method for pruning graph lines. */
	for (i = 0; i < graph->size; i++)
		if (!strncmp(graph->rev[i], parent, SIZEOF_REV))
			return;

	if (graph->size < SIZEOF_REVITEMS) {
		string_ncopy(graph->rev[graph->size++], parent, SIZEOF_REV);
	}
}

static chtype
get_rev_graph_symbol(struct rev_graph *graph)
{
	chtype symbol;

	if (graph->parents->size == 0)
		symbol = REVGRAPH_INIT;
	else if (graph_parent_is_merge(graph))
		symbol = REVGRAPH_MERGE;
	else if (graph->pos >= graph->size)
		symbol = REVGRAPH_BRANCH;
	else
		symbol = REVGRAPH_COMMIT;

	return symbol;
}

static void
draw_rev_graph(struct rev_graph *graph)
{
	struct rev_filler {
		chtype separator, line;
	};
	enum { DEFAULT, RSHARP, RDIAG, LDIAG };
	static struct rev_filler fillers[] = {
		{ ' ',	REVGRAPH_LINE },
		{ '`',	'.' },
		{ '\'',	' ' },
		{ '/',	' ' },
	};
	chtype symbol = get_rev_graph_symbol(graph);
	struct rev_filler *filler;
	size_t i;

	filler = &fillers[DEFAULT];

	for (i = 0; i < graph->pos; i++) {
		append_to_rev_graph(graph, filler->line);
		if (graph_parent_is_merge(graph->prev) &&
		    graph->prev->pos == i)
			filler = &fillers[RSHARP];

		append_to_rev_graph(graph, filler->separator);
	}

	/* Place the symbol for this revision. */
	append_to_rev_graph(graph, symbol);

	if (graph->prev->size > graph->size)
		filler = &fillers[RDIAG];
	else
		filler = &fillers[DEFAULT];

	i++;

	for (; i < graph->size; i++) {
		append_to_rev_graph(graph, filler->separator);
		append_to_rev_graph(graph, filler->line);
		if (graph_parent_is_merge(graph->prev) &&
		    i < graph->prev->pos + graph->parents->size)
			filler = &fillers[RSHARP];
		if (graph->prev->size > graph->size)
			filler = &fillers[LDIAG];
	}

	if (graph->prev->size > graph->size) {
		append_to_rev_graph(graph, filler->separator);
		if (filler->line != ' ')
			append_to_rev_graph(graph, filler->line);
	}
}

/* Prepare the next rev graph */
static void
prepare_rev_graph(struct rev_graph *graph)
{
	size_t i;

	/* First, traverse all lines of revisions up to the active one. */
	for (graph->pos = 0; graph->pos < graph->size; graph->pos++) {
		if (!strcmp(graph->rev[graph->pos], graph->commit->id))
			break;

		push_rev_graph(graph->next, graph->rev[graph->pos]);
	}

	/* Interleave the new revision parent(s). */
	for (i = 0; i < graph->parents->size; i++)
		push_rev_graph(graph->next, graph->parents->rev[i]);

	/* Lastly, put any remaining revisions. */
	for (i = graph->pos + 1; i < graph->size; i++)
		push_rev_graph(graph->next, graph->rev[i]);
}

static void
update_rev_graph(struct rev_graph *graph)
{
	/* If this is the finalizing update ... */
	if (graph->commit)
		prepare_rev_graph(graph);

	/* Graph visualization needs a one rev look-ahead,
	 * so the first update doesn't visualize anything. */
	if (!graph->prev->commit)
		return;

	draw_rev_graph(graph->prev);
	done_rev_graph(graph->prev->prev);
}


/*
 * Main view backend
 */

		waddch(view->win, ' ');
			else if (commit->refs[i]->remote)
				wattrset(view->win, get_line_attr(LINE_MAIN_REMOTE));
	static struct rev_graph *graph = graph_stacks;
	enum line_type type;
	struct commit *commit;
	if (!line) {
		update_rev_graph(graph);
		return TRUE;
	}

	type = get_line_type(line);
	if (type == LINE_COMMIT) {
		string_copy_rev(commit->id, line + STRING_SIZE("commit "));
		add_line_data(view, commit, LINE_MAIN_COMMIT);
		return TRUE;
	}
	if (!view->lines)
		return TRUE;
	commit = view->line[view->lines - 1].data;

	switch (type) {
		push_rev_graph(graph->parents, line + STRING_SIZE("parent "));
		/* Parse author lines where the name may be empty:
		 *	author  <email@address.tld> 1138474660 +0100
		 */
		char *nameend = strchr(ident, '<');
		char *emailend = strchr(ident, '>');
		if (!nameend || !emailend)
		*nameend = *emailend = 0;
		ident = chomp_string(ident);
		if (!*ident) {
			ident = chomp_string(nameend + 1);
			if (!*ident)
				ident = "Unknown";
		if (emailend[1] == ' ') {
			char *secs = emailend + 2;
			char *zone = strchr(secs, ' ');
			time_t time = (time_t) atol(secs);

		if (strncmp(line, "    ", 4))
		line += 4;
		/* Well, if the title starts with a whitespace character,
		 * try to be forgiving.  Otherwise we end up with no title. */
		while (isspace(*line))
			line++;
		if (*line == '\0')
			break;
		/* FIXME: More graceful handling of titles; append "..." to
		 * shortened titles, etc. */
		string_copy(commit->title, line);
	string_copy_rev(view->ref, commit->id);
	string_copy_rev(ref_commit, view->ref);
	NULL,
	main_draw,
static bool status_empty = TRUE;

	if (input_mode)
		return;

	if (!status_empty || *msg) {
			status_empty = FALSE;
			status_empty = TRUE;
		wclrtoeol(status_win);
	update_display_cursor(view);
		input_mode = TRUE;

		input_mode = FALSE;

		mvwprintw(status_win, 0, 0, "%s%.*s", prompt, pos, buf);
		wclrtoeol(status_win);

	/* Clear the status window */
	status_empty = FALSE;
	report("");

	if (status == CANCEL)
	bool remote = FALSE;
	} else if (!strncmp(name, "refs/remotes/", STRING_SIZE("refs/remotes/"))) {
		remote = TRUE;
		namelen -= STRING_SIZE("refs/remotes/");
		name	+= STRING_SIZE("refs/remotes/");

	ref->remote = remote;
	string_copy_rev(ref->id, id);
		/* wgetch() with nodelay() enabled returns ERR when there's no
		 * input. */
		if (key == ERR) {
			request = REQ_NONE;
			continue;
		}
