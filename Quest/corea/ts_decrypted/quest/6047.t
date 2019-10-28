CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6047;
	title = 604702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "100;3;";

			CDboTSActNPCConv
			{
				conv = 604725;
				ctype = 1;
				idx = 4371402;
				taid = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "7;100;";
			type = 1;
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
				npcidx = 4371402;
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
				clsflg = 1572864;
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
				conv = 604727;
				ctype = 1;
				idx = 4371402;
				taid = 1;
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
				conv = 604709;
				ctype = 1;
				idx = 4152103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 604708;
				gtype = 1;
				area = 604701;
				goal = 604704;
				grade = -1;
				rwd = 100;
				sort = 604705;
				stype = 8;
				taid = 1;
				title = 604702;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 3;
			desc = 604714;
			nextlnk = 4;
			rwdtbl = 604702;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371402;
			}
		}
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			desc = 604726;
			nextlnk = 253;
			rwdtbl = 604701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "6;";
			usetbl = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 604707;
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
				and = "6046;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 604708;
			gtype = 1;
			oklnk = 2;
			area = 604701;
			goal = 604704;
			sort = 604705;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 604702;
		}
	}
}

