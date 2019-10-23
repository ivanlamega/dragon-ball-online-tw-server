CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6046;
	title = 604602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActWorldPlayScript
			{
				sid = 6046;
				start = 0;
				taid = 2;
				uof = 0;
			}
			CDboTSActETimerE
			{
				taeid = 5;
				taid = 1;
				tceid = 2;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 254;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActETimerS
			{
				sort = 0;
				taid = 5;
				tgid = 1;
				time = 600000;
			}
			CDboTSActNPCConv
			{
				conv = 604609;
				ctype = 1;
				idx = 4152103;
				taid = 1;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6046;
				start = 1;
				taid = 4;
				uof = 0;
			}
			CDboTSActRegQInfo
			{
				cont = 604608;
				gtype = 3;
				area = 604601;
				goal = 604604;
				m0fz = "-2426.000000";
				m0widx = 1;
				sort = 604605;
				stype = 8;
				m0fy = "-37.000000";
				grade = -1;
				m0fx = "4374.000000";
				m0ttip = 604615;
				rwd = 100;
				taid = 3;
				title = 604602;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6681200;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 604614;
			nextlnk = 5;
			rwdtbl = 604601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4152103;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "5;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 604607;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 64;
			}
			CDboTSClickNPC
			{
				npcidx = 4152103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6045;";
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;1;0;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 604608;
			gtype = 3;
			oklnk = 2;
			area = 604601;
			goal = 604604;
			sort = 604605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 604602;
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 253;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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

