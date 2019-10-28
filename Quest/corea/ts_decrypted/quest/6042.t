CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6042;
	title = 604202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 604209;
				ctype = 1;
				idx = 4371402;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 604208;
				gtype = 1;
				area = 604201;
				goal = 604204;
				grade = -1;
				rwd = 100;
				sort = 604205;
				stype = 8;
				taid = 1;
				title = 604202;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 604207;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 64;
			}
			CDboTSClickNPC
			{
				npcidx = 4371402;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6011;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 604214;
			nextlnk = 253;
			rwdtbl = 604201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7071104;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 604208;
			gtype = 1;
			oklnk = 2;
			area = 604201;
			goal = 604204;
			sort = 604205;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 604202;
		}
	}
}

