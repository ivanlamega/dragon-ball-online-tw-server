CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6041;
	title = 604102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 7;
			elnk = 255;
			nextlnk = 253;
			prelnk = "6;";

			CDboTSActNPCConv
			{
				conv = 604127;
				ctype = 1;
				idx = 4141101;
				taid = 1;
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
				clsflg = 393216;
			}
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "4;";
			nolnk = 255;
			rm = 1;
			yeslnk = 6;

			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;7;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "100;3;";

			CDboTSActNPCConv
			{
				conv = 604125;
				ctype = 1;
				idx = 4141101;
				taid = 1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 3;
			desc = 604114;
			nextlnk = 4;
			rwdtbl = 604102;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 604107;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3611101;
			}
			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6040;";
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 604109;
				ctype = 1;
				idx = 3611101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 604108;
				gtype = 1;
				area = 604101;
				goal = 604104;
				grade = -1;
				rwd = 100;
				sort = 604105;
				stype = 8;
				taid = 1;
				title = 604102;
			}
		}
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			desc = 604126;
			nextlnk = 253;
			rwdtbl = 604101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "6;";
			usetbl = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 604108;
			gtype = 1;
			oklnk = 2;
			area = 604101;
			goal = 604104;
			sort = 604105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 604102;
		}
	}
}

