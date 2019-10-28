CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6024;
	title = 602402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 602409;
				ctype = 1;
				idx = 3181301;
				taid = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 602408;
				gtype = 1;
				area = 602401;
				goal = 602404;
				grade = -1;
				rwd = 100;
				sort = 602405;
				stype = 8;
				taid = 2;
				title = 602402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 2;
				idx0 = 702;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 703;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 8;
			elnk = 255;
			nextlnk = 5;
			prelnk = "100;4;";

			CDboTSActNPCConv
			{
				conv = 602425;
				ctype = 1;
				idx = 3221201;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 8;
			prelnk = "3;";

			CDboTSActQItem
			{
				icnt0 = 1;
				iprob0 = "1.000000";
				iidx0 = 702;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
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
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "8;";
			nolnk = 255;
			rm = 1;
			yeslnk = 6;

			CDboTSClickNPC
			{
				npcidx = 3221201;
			}
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "5;";
			nolnk = 100;
			rm = 0;
			yeslnk = 7;

			CDboTSCheckPCCls
			{
				clsflg = 1536;
			}
		}
		CDboTSContGAct
		{
			cid = 7;
			elnk = 255;
			nextlnk = 253;
			prelnk = "6;";

			CDboTSActNPCConv
			{
				conv = 602427;
				ctype = 1;
				idx = 3221201;
				taid = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 3;
			desc = 602414;
			nextlnk = 4;
			rwdtbl = 602402;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3221201;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 703;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 702;
			}
		}
		CDboTSContReward
		{
			canclnk = 8;
			cid = 100;
			desc = 602426;
			nextlnk = 253;
			rwdtbl = 602401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "6;";
			usetbl = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "7;100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 602407;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3181301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6023;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602408;
			gtype = 1;
			oklnk = 2;
			area = 602401;
			goal = 602404;
			sort = 602405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602402;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 5;
			prelnk = "2;4;";
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
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 2;
			rm = 0;
			yeslnk = 3;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 702;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "2;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 703;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 2;
			prelnk = "1;3;";
			nolnk = 5;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 703;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 2;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 702;
				taid = 1;
				type = 1;
			}
		}
	}
}

