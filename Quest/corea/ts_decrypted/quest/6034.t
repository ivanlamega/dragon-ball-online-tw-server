CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6034;
	title = 603402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 6;
			prelnk = "4;";

			CDboTSActSendSvrEvt
			{
				id = 208;
				tblidx = 6034;
				stradius = 200;
				stype = 3;
				taid = 1;
				ttype = 255;
				type = 6;
			}
			CDboTSActSendSvrEvt
			{
				id = 603401;
				tblidx = 3174103;
				stradius = 200;
				stype = 3;
				taid = 2;
				ttype = 255;
				type = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 100;
			prelnk = "5;";

			CDboTSActETimerE
			{
				taeid = 2;
				taid = 1;
				tceid = 3;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6034;
				start = 0;
				taid = 2;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 253;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActETimerS
			{
				sort = 0;
				taid = 2;
				tgid = 1;
				time = 900000;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6034;
				start = 1;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 603407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
			CDboTSCheckClrQst
			{
				and = "6033;";
			}
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSSkillUse
			{
				idx = 420111;
				rp = 0;
				stype = 3;
				tidx = 3174103;
				ttype = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 603409;
				ctype = 1;
				idx = 4511101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 603408;
				gtype = 2;
				area = 603401;
				goal = 603404;
				m0fz = "4218.390137";
				m0widx = 1;
				sort = 603405;
				stype = 8;
				m0fy = "0.000000";
				grade = -1;
				m0fx = "6100.250000";
				m0ttip = 603415;
				rwd = 100;
				taid = 1;
				title = 603402;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "3;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 603414;
			nextlnk = 254;
			rwdtbl = 603401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "6;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 603408;
			gtype = 2;
			oklnk = 2;
			area = 603401;
			goal = 603404;
			sort = 603405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 603402;
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
	}
}

